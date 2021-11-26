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

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;

using circlet::v1::RedirectService;
using circlet::v1::CreateRedirectRequest;
using circlet::v1::Redirect;

class RedirectServiceImpl final : public RedirectService::Service {
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

        response->set_from_location(from_location);
        response->set_to_location("/test");

        return Status::OK;
  }
};

void run_server() {
    auto server_address = "0.0.0.0:50051";

    auto service = RedirectServiceImpl();

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "RedirectService listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char** argv) {
    run_server();
    return 0;
}
