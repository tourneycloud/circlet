// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: redirectservice.proto
// Original file comments:
//
// Copyright 2021 Michael P. Nitowski
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef GRPC_redirectservice_2eproto__INCLUDED
#define GRPC_redirectservice_2eproto__INCLUDED

#include "redirectservice.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace circlet {
namespace v1 {

class RedirectService final {
 public:
  static constexpr char const* service_full_name() {
    return "circlet.v1.RedirectService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status CreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::circlet::v1::Redirect* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::circlet::v1::Redirect>> AsyncCreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::circlet::v1::Redirect>>(AsyncCreateShortenedRedirectRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::circlet::v1::Redirect>> PrepareAsyncCreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::circlet::v1::Redirect>>(PrepareAsyncCreateShortenedRedirectRaw(context, request, cq));
    }
    // option (google.api.http) = {
    //     post: "/v1/redirects:shorten"
    //     body: "redirect"
    // };
    class async_interface {
     public:
      virtual ~async_interface() {}
      virtual void CreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest* request, ::circlet::v1::Redirect* response, std::function<void(::grpc::Status)>) = 0;
      virtual void CreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest* request, ::circlet::v1::Redirect* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      // option (google.api.http) = {
      //     post: "/v1/redirects:shorten"
      //     body: "redirect"
      // };
    };
    typedef class async_interface experimental_async_interface;
    virtual class async_interface* async() { return nullptr; }
    class async_interface* experimental_async() { return async(); }
   private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::circlet::v1::Redirect>* AsyncCreateShortenedRedirectRaw(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::circlet::v1::Redirect>* PrepareAsyncCreateShortenedRedirectRaw(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    ::grpc::Status CreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::circlet::v1::Redirect* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::circlet::v1::Redirect>> AsyncCreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::circlet::v1::Redirect>>(AsyncCreateShortenedRedirectRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::circlet::v1::Redirect>> PrepareAsyncCreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::circlet::v1::Redirect>>(PrepareAsyncCreateShortenedRedirectRaw(context, request, cq));
    }
    class async final :
      public StubInterface::async_interface {
     public:
      void CreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest* request, ::circlet::v1::Redirect* response, std::function<void(::grpc::Status)>) override;
      void CreateShortenedRedirect(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest* request, ::circlet::v1::Redirect* response, ::grpc::ClientUnaryReactor* reactor) override;
     private:
      friend class Stub;
      explicit async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class async* async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::circlet::v1::Redirect>* AsyncCreateShortenedRedirectRaw(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::circlet::v1::Redirect>* PrepareAsyncCreateShortenedRedirectRaw(::grpc::ClientContext* context, const ::circlet::v1::CreateRedirectRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_CreateShortenedRedirect_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status CreateShortenedRedirect(::grpc::ServerContext* context, const ::circlet::v1::CreateRedirectRequest* request, ::circlet::v1::Redirect* response);
    // option (google.api.http) = {
    //     post: "/v1/redirects:shorten"
    //     body: "redirect"
    // };
  };
  template <class BaseClass>
  class WithAsyncMethod_CreateShortenedRedirect : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_CreateShortenedRedirect() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_CreateShortenedRedirect() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateShortenedRedirect(::grpc::ServerContext* /*context*/, const ::circlet::v1::CreateRedirectRequest* /*request*/, ::circlet::v1::Redirect* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestCreateShortenedRedirect(::grpc::ServerContext* context, ::circlet::v1::CreateRedirectRequest* request, ::grpc::ServerAsyncResponseWriter< ::circlet::v1::Redirect>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_CreateShortenedRedirect<Service > AsyncService;
  template <class BaseClass>
  class WithCallbackMethod_CreateShortenedRedirect : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithCallbackMethod_CreateShortenedRedirect() {
      ::grpc::Service::MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::circlet::v1::CreateRedirectRequest, ::circlet::v1::Redirect>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::circlet::v1::CreateRedirectRequest* request, ::circlet::v1::Redirect* response) { return this->CreateShortenedRedirect(context, request, response); }));}
    void SetMessageAllocatorFor_CreateShortenedRedirect(
        ::grpc::MessageAllocator< ::circlet::v1::CreateRedirectRequest, ::circlet::v1::Redirect>* allocator) {
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
      static_cast<::grpc::internal::CallbackUnaryHandler< ::circlet::v1::CreateRedirectRequest, ::circlet::v1::Redirect>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~WithCallbackMethod_CreateShortenedRedirect() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateShortenedRedirect(::grpc::ServerContext* /*context*/, const ::circlet::v1::CreateRedirectRequest* /*request*/, ::circlet::v1::Redirect* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* CreateShortenedRedirect(
      ::grpc::CallbackServerContext* /*context*/, const ::circlet::v1::CreateRedirectRequest* /*request*/, ::circlet::v1::Redirect* /*response*/)  { return nullptr; }
  };
  typedef WithCallbackMethod_CreateShortenedRedirect<Service > CallbackService;
  typedef CallbackService ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_CreateShortenedRedirect : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_CreateShortenedRedirect() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_CreateShortenedRedirect() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateShortenedRedirect(::grpc::ServerContext* /*context*/, const ::circlet::v1::CreateRedirectRequest* /*request*/, ::circlet::v1::Redirect* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_CreateShortenedRedirect : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_CreateShortenedRedirect() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_CreateShortenedRedirect() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateShortenedRedirect(::grpc::ServerContext* /*context*/, const ::circlet::v1::CreateRedirectRequest* /*request*/, ::circlet::v1::Redirect* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestCreateShortenedRedirect(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawCallbackMethod_CreateShortenedRedirect : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawCallbackMethod_CreateShortenedRedirect() {
      ::grpc::Service::MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
                   ::grpc::CallbackServerContext* context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->CreateShortenedRedirect(context, request, response); }));
    }
    ~WithRawCallbackMethod_CreateShortenedRedirect() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status CreateShortenedRedirect(::grpc::ServerContext* /*context*/, const ::circlet::v1::CreateRedirectRequest* /*request*/, ::circlet::v1::Redirect* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    virtual ::grpc::ServerUnaryReactor* CreateShortenedRedirect(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)  { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_CreateShortenedRedirect : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_CreateShortenedRedirect() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::circlet::v1::CreateRedirectRequest, ::circlet::v1::Redirect>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::circlet::v1::CreateRedirectRequest, ::circlet::v1::Redirect>* streamer) {
                       return this->StreamedCreateShortenedRedirect(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_CreateShortenedRedirect() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status CreateShortenedRedirect(::grpc::ServerContext* /*context*/, const ::circlet::v1::CreateRedirectRequest* /*request*/, ::circlet::v1::Redirect* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedCreateShortenedRedirect(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::circlet::v1::CreateRedirectRequest,::circlet::v1::Redirect>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_CreateShortenedRedirect<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_CreateShortenedRedirect<Service > StreamedService;
};

}  // namespace v1
}  // namespace circlet


#endif  // GRPC_redirectservice_2eproto__INCLUDED
