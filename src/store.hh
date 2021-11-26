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

#include <liburing.h>

class CircletStore {
    private:
        int client_fd;
        struct io_uring ring;
        bool connected = false;

    protected:
        void _ensure_connected();
        std::string _make_request(std::string request);

    public:
        std::string connection_string;

        CircletStore(std::string connection_string);
        ~CircletStore();

        void record_redirect(std::string path);
        std::string get_redirect_path(std::string path);
};
