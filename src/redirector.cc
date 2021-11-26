/*
 * Copyright 2021 Michael P. Nitowski
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <string>

extern "C" {
    #include <stdlib.h>
    #include <string.h>
}

#include <liburing.h>

#include "log.hh"
#include "redirector.hh"

CircletRedirector::CircletRedirector(CircletStore* store, int port, std::string default_redirect_base_url) {
    this->store = store;
    this->port = port;
    this->default_redirect_base_url = default_redirect_base_url;
    this->queue_depth = DEFAULT_QUEUE_DEPTH;
}

CircletRedirector::~CircletRedirector() {
    io_uring_queue_exit(&this->ring);
}

void CircletRedirector::_initialize_socket() {
    this->listen_fd = socket(AF_INET6, SOCK_STREAM, 0);

    if (this->listen_fd == -1) {
        fatal("socket() call failed");
    }

    this->address.sin6_family = AF_INET6;
    this->address.sin6_port = htons(this->port);
    this->address.sin6_addr = in6addr_any;

    int opt = 1;
    if (setsockopt(this->listen_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        fatal("setsockopt() call failed");
    }
    if (bind(this->listen_fd, (struct sockaddr*) &this->address, sizeof(this->address)) < 0) {
        fatal("bind() call failed");
    }

    int backlog = 0x7f;
    if (listen(this->listen_fd, backlog) < 0) {
        fatal("listen() call failed");
    }

    std::cout << "Starting Circlet on port " << this->port << std::endl;
}

void CircletRedirector::_initialize_ring() {
    io_uring_queue_init(this->queue_depth, &this->ring, 0);
}

void CircletRedirector::_accept(struct sockaddr_in *client_addr) {
    struct io_uring_sqe *sqe = io_uring_get_sqe(&this->ring);
    socklen_t client_addr_len = sizeof(client_addr);
    io_uring_prep_accept(sqe, this->listen_fd, (struct sockaddr*) client_addr, &client_addr_len, 0);
    auto req = new RedirectRequest(RedirectRequest::EventType::accept);
    io_uring_sqe_set_data(sqe, req);
    io_uring_submit(&this->ring);
}

void CircletRedirector::_read(int client_fd) {
    struct io_uring_sqe *sqe = io_uring_get_sqe(&this->ring);
    auto req = new RedirectRequest(RedirectRequest::EventType::read);
    req->client_fd = client_fd;
    io_uring_prep_read(sqe, client_fd, req->buffer, DEFAULT_REQUEST_BUFFER_SIZE, 0);
    io_uring_sqe_set_data(sqe, req);
    io_uring_submit(&this->ring);
}

void CircletRedirector::_write(RedirectRequest* req) {
    struct io_uring_sqe *sqe = io_uring_get_sqe(&this->ring);
    req->event_type = RedirectRequest::EventType::write;
    io_uring_prep_write(sqe, req->client_fd, req->buffer, strlen(req->buffer), 0);
    io_uring_sqe_set_data(sqe, req);
    io_uring_submit(&this->ring);
}

void CircletRedirector::_handle_request(RedirectRequest* req) {
    auto buf = req->buffer;

    std::string buffer = std::string((const char*) buf, DEFAULT_REQUEST_BUFFER_SIZE);

    buffer.resize(buffer.find_first_of('\0'));
    std::string first_line = buffer.substr(0, buffer.find_first_of("\r\n"));
    std::string method = first_line.substr(0, first_line.find_first_of(" "));
    std::string path = first_line.substr(
        first_line.find_first_of(" ") + 1,
        first_line.find_first_of(" ?", first_line.find_first_of(" ") + 1) - first_line.find_first_of(" ") - 1
    );

    std::string redirect_path = this->store->get_redirect_path(path);

    std::string response;
    if (redirect_path == "") {
        response = "HTTP/1.1 404 Not Found\r\nConnection: close\r\n\r\n";
    } else {
        std::string location = this->default_redirect_base_url + redirect_path;

        response = "HTTP/1.1 301 Moved Permanently\r\n";
        response.append("Cache-Control: private, max-age=60\r\n");
        response.append("Location: ");
        response.append(location);
        response.append("\r\n");
        response.append("Connection: close\r\n");
        response.append("\r\n");
    }

    auto response_str = response.c_str();
    size_t response_str_length = strlen(response_str);

    auto write_req = new RedirectRequest(RedirectRequest::EventType::write);
    write_req->client_fd = req->client_fd;
    memcpy(write_req->buffer, response_str, response_str_length);
    this->_write(write_req);

    if (redirect_path != "") {
        this->store->record_redirect(path);
    }
}

void CircletRedirector::serve() {
    this->_initialize_socket();
    this->_initialize_ring();

    struct io_uring_cqe *cqe;
    struct sockaddr_in client_addr;

    this->_accept(&client_addr);
    while (true) {
        if (io_uring_wait_cqe(&this->ring, &cqe) < 0) {
            fatal("io_uring_wait_cqe() call failed");
        }

        RedirectRequest* req = (RedirectRequest*) cqe->user_data;
        if (cqe->res < 0) {
            fatal("Failed to handle event " + std::to_string(req->event_type));
        }

        switch (req->event_type) {
            case RedirectRequest::EventType::accept: {
                this->_accept(&client_addr);
                this->_read(cqe->res);
                break;
            }
            case RedirectRequest::EventType::read: {
                if (!cqe->res) {
                    std::cerr << "Encountered empty request" << std::endl;
                    break;
                }
                this->_handle_request(req);
                break;
            }
            case RedirectRequest::EventType::write: {
                close(req->client_fd);
                break;
            }
        }

        delete req;

        // Mark request as complete
        io_uring_cqe_seen(&this->ring, cqe);
    }
}

void handle_sigint(int signum) {
    std::cout << "Received SIGINT: shutting down" << std::endl;
    std::exit(130);
}

int main(int argc, char* argv[]) {
    signal(SIGINT, handle_sigint);

    auto default_redirect_base_url = argc > 1 ? std::string(argv[1]) : "http://localhost:8080";
    auto store_connection_string = argc > 2 ? std::string(argv[2]) : "localhost:6379";
    auto port = argc > 3 ? std::atoi(argv[3]) : DEFAULT_PORT;
    if (port < MIN_PORT || port > MAX_PORT) {
        fatal("Invalid port provided: shutting down");
    }

    auto store = new CircletStore(store_connection_string);

    auto redirector = new CircletRedirector(store, port);
    redirector->default_redirect_base_url = default_redirect_base_url;
    redirector->serve();

    return 0;
}
