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
#include <memory>
#include <string>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "redirectservice.grpc.pb.h"

#include "log.hh"
#include "store.hh"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;

using circlet::v1::RedirectService;
using circlet::v1::CreateRedirectRequest;
using circlet::v1::Redirect;

class RedirectServiceImpl final : public RedirectService::Service {
    private:
        CircletStore* store;

    public:
        void attach_store(CircletStore* store) {
            this->store = store;
        }

        CircletStore* get_store() {
            if (!this->store) {
                fatal("Store is unattached which is necessary to fulfill Redirect Service methods");
            }

            return this->store;
        }

        Status CreateShortenedRedirect(
            ServerContext* context,
            const CreateRedirectRequest* request,
            Redirect* response
        ) override {
            auto from_location = request->redirect().from_location();
            if (from_location == "") {
                return Status(StatusCode::INVALID_ARGUMENT, "Must provide from_location as path or url");
            }

            if (request->redirect().to_location() != "") {
                return Status(
                    StatusCode::INVALID_ARGUMENT,
                    "Must not set to_location in this endpoint since it will be generated in the response"
                );
            }

            this->get_store()->create_redirect(from_location, "/test");

            response->set_from_location(from_location);
            response->set_to_location("/test");

            return Status::OK;
    }
};

void handle_sigint(int signum) {
    std::cout << "Received SIGINT: shutting down" << std::endl;
    std::exit(130);
}

int main(int argc, char* argv[]) {
    signal(SIGINT, handle_sigint);

    auto bind_address = argc > 1 ? std::string(argv[1]) : "0.0.0.0:50051";
    auto store_connection_string = argc > 2 ? std::string(argv[2]) : "localhost:6379";

    auto store = new CircletStore(store_connection_string);

    auto service = RedirectServiceImpl();
    service.attach_store(store);

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    builder.AddListeningPort(bind_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());

    std::cout << "RedirectService listening on " << bind_address << std::endl;
    server->Wait();

    return 0;
}
