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

#include <string>

extern "C" {
    #include <netdb.h>
    #include <netinet/in.h>
    #include <unistd.h>
}

#include <liburing.h>

#include "store.hh"

#define DEFAULT_PORT 3001
#define DEFAULT_QUEUE_DEPTH 256
#define DEFAULT_REQUEST_BUFFER_SIZE 1024
#define MIN_PORT 1
#define MAX_PORT 65535

class RedirectRequest {
    public:
        enum EventType { accept, read, write };

        EventType event_type;

        int client_fd;
        char buffer[DEFAULT_REQUEST_BUFFER_SIZE];

        RedirectRequest(EventType event_type) {
            this->event_type = event_type;
        }
};

class CircletRedirector {
    private:
        int port;
        int queue_depth;

        int listen_fd;
        struct sockaddr_in6 address;
        struct io_uring ring;

    protected:
        CircletStore* store;

        void _initialize_socket();
        void _initialize_ring();

        void _accept(struct sockaddr_in *client_addr);
        void _read(int client_fd);
        void _write(RedirectRequest* req);
        void _handle_request(RedirectRequest* req);

    public:
        std::string default_redirect_base_url;

        CircletRedirector(CircletStore* store, int port = DEFAULT_PORT, std::string default_redirect_base_url = "");
        ~CircletRedirector();

        void serve();
};
