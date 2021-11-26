// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: redirectservice.proto

#include "redirectservice.pb.h"
#include "redirectservice.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace circlet {
namespace v1 {

static const char* RedirectService_method_names[] = {
  "/circlet.v1.RedirectService/CreateShortenedRedirect",
};

std::unique_ptr< RedirectService::Stub> RedirectService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< RedirectService::Stub> stub(new RedirectService::Stub(channel, options));
  return stub;
}

RedirectService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_CreateShortenedRedirect_(RedirectService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status RedirectService::Stub::CreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::circlet::v1::Redirect* response) {
  return ::grpc::internal::BlockingUnaryCall< ::circlet::v1::CreateRedirectRequest, ::circlet::v1::Redirect, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CreateShortenedRedirect_, context, request, response);
}

void RedirectService::Stub::async::CreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest* request, ::circlet::v1::Redirect* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::circlet::v1::CreateRedirectRequest, ::circlet::v1::Redirect, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CreateShortenedRedirect_, context, request, response, std::move(f));
}

void RedirectService::Stub::async::CreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest* request, ::circlet::v1::Redirect* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CreateShortenedRedirect_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::circlet::v1::Redirect>* RedirectService::Stub::PrepareAsyncCreateShortenedRedirectRaw(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::circlet::v1::Redirect, ::circlet::v1::CreateRedirectRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CreateShortenedRedirect_, context, request);
}

::grpc::ClientAsyncResponseReader< ::circlet::v1::Redirect>* RedirectService::Stub::AsyncCreateShortenedRedirectRaw(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCreateShortenedRedirectRaw(context, request, cq);
  result->StartCall();
  return result;
}

RedirectService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      RedirectService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< RedirectService::Service, ::circlet::v1::CreateRedirectRequest, ::circlet::v1::Redirect, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](RedirectService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::circlet::v1::CreateRedirectRequest* req,
             ::circlet::v1::Redirect* resp) {
               return service->CreateShortenedRedirect(ctx, req, resp);
             }, this)));
}

RedirectService::Service::~Service() {
}

::grpc::Status RedirectService::Service::CreateShortenedRedirect(::grpc::ServerContext* context, const ::circlet::v1::CreateRedirectRequest* request, ::circlet::v1::Redirect* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace circlet
}  // namespace v1
