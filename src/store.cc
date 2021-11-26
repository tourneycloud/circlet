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
    #include <netdb.h>
    #include <netinet/in.h>
    #include <unistd.h>
}

#include "log.hh"
#include "store.hh"

CircletStore::CircletStore(std::string connection_string) {
    this->connection_string = connection_string;
    io_uring_queue_init(256, &this->ring, 0);
}

CircletStore::~CircletStore() {
    io_uring_queue_exit(&this->ring);
}

void CircletStore::_ensure_connected() {
    if (this->connected) {
        return;
    }

    this->client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->client_fd < 0) {
        fatal("Could not create socket for CircletStore");
    }


    auto split_index = this->connection_string.find(':');
    auto host = this->connection_string.substr(0, split_index);
    auto port = std::atoi(
        this->connection_string.substr(
            split_index + 1,
            this->connection_string.size() - split_index
        ).c_str()
    );

    auto server = gethostbyname(host.c_str());
    if (server == NULL) {
        fatal("Could not find server for CircletStore");
    }


    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(this->client_fd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0) {
        fatal("Could not connect to server for CircletStore");
    }

    std::cout << "Connected to CircletStore" << std::endl;
    this->connected = true;
}

std::string CircletStore::_make_request(std::string request) {
    this->_ensure_connected();

    struct io_uring_sqe* sqe;
    struct io_uring_cqe* cqe;

    auto request_with_newline = request + "\n";
    auto request_str = request_with_newline.c_str();
    auto request_str_len = strlen(request_str);

    sqe = io_uring_get_sqe(&this->ring);
    if (!sqe) {
        fatal("io_uring_get_sqe() failed");
    }

    io_uring_prep_write(sqe, this->client_fd, request_str, request_str_len, 0);
    sqe->flags |= IOSQE_IO_LINK;

    sqe = io_uring_get_sqe(&this->ring);
    if (!sqe) {
        fatal("io_uring_get_sqe() failed");
    }

    io_uring_prep_write(sqe, this->client_fd, request_str, request_str_len, 0);

    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    io_uring_prep_read(sqe, client_fd, buffer, 4096, 0);

    io_uring_submit(&this->ring);

    if (io_uring_wait_cqe(&this->ring, &cqe) < 0) {
        fatal("io_uring_wait_cqe() failed");
    }
    if (cqe->res < 0) {
        fatal(strerror(-cqe->res));
    }
    io_uring_cqe_seen(&this->ring, cqe);

    if (io_uring_wait_cqe(&this->ring, &cqe) < 0) {
        fatal("io_uring_wait_cqe() failed");
    }
    if (cqe->res < 0) {
        fatal(strerror(-cqe->res));
    }
    io_uring_cqe_seen(&this->ring, cqe);

    std::string response = std::string(buffer, 4096);
    response.resize(response.find_first_of('\0'));

    return response;
}

void CircletStore::record_redirect(std::string path) {
    auto response = this->_make_request("incr " + ("visits_" + path));
    if (response.substr(0, 1) == "-") {
        std::cerr << "Failed to record redirect" << std::endl;
    }
}

std::string CircletStore::get_redirect_path(std::string path) {
    this->_ensure_connected();

    struct io_uring_sqe* sqe;
    struct io_uring_cqe* cqe;

    auto get_key = "get " + path + "\n";
    auto get_key_str = get_key.c_str();
    auto get_key_len = strlen(get_key_str);

    sqe = io_uring_get_sqe(&this->ring);
    if (!sqe) {
        fatal("io_uring_get_sqe() failed");
    }

    io_uring_prep_write(sqe, this->client_fd, get_key_str, get_key_len, 0);
    sqe->flags |= IOSQE_IO_LINK;

    sqe = io_uring_get_sqe(&this->ring);
    if (!sqe) {
        fatal("io_uring_get_sqe() failed");
    }

    io_uring_prep_write(sqe, this->client_fd, get_key_str, get_key_len, 0);

    char buffer[2048];
    memset(buffer, 0, sizeof(buffer));
    io_uring_prep_read(sqe, client_fd, buffer, 2048, 0);

    io_uring_submit(&this->ring);

    io_uring_wait_cqe(&this->ring, &cqe);
    io_uring_cqe_seen(&this->ring, cqe);
    io_uring_wait_cqe(&this->ring, &cqe);
    io_uring_cqe_seen(&this->ring, cqe);

    std::string value = std::string(buffer, 2048);
    if (value.substr(0, value.find_first_of('\n') - 1) == "$-1") {
        return "";  // Empty value
    }

    return value.substr(
        value.find_first_of('\n') + 1,
        value.find_first_of('\0') - value.find_first_of('\n') - 3
    );
}
