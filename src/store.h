 
#include "threadpool.h"

//NOTE: Part of implementation is taken from hello world async example on grpc github

#include <fstream>

#include <grpc++/grpc++.h>
#include <string>
#include "vendor.grpc.pb.h"
#include "vendor.pb.h"
#include "store.grpc.pb.h"
#include "store.pb.h"
#include <unistd.h>

#include <iostream>

using std::to_string;
using std::shared_ptr;
using grpc::Server;
using grpc::ServerAsyncResponseWriter;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerCompletionQueue;
using grpc::Status;
using store::ProductQuery;
using store::ProductReply;
using store::ProductInfo;
using store::Store;
using std::string;
using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;
using vendor::BidQuery;
using vendor::BidReply;
using vendor::Vendor;
using std::cout;
using std::endl;


typedef struct bidFinishInfo{
    std::shared_ptr<ClientAsyncResponseReader<BidReply>> rpc;
    std::shared_ptr<CompletionQueue> cq;
    std::shared_ptr<ClientContext> ctx;
    std::shared_ptr<BidReply> vr;
    std::shared_ptr<Status> st;
} BidFinishInfo;





class VendorClientChannel {
 public:
  explicit VendorClientChannel(std::shared_ptr<Channel> channel)
      : stub_(Vendor::NewStub(channel)) {}

   std::shared_ptr<BidFinishInfo> getProductBid(const std::string& product);

    std::shared_ptr<BidReply> getVendorResult(std::shared_ptr<BidFinishInfo> bfi);

 private:
  std::unique_ptr<Vendor::Stub> stub_;
};


typedef struct blockingThreadpoolVendorCallerData{
    mutex my_thread_mutex;//caller can block on this to get status of job
    VendorClientChannel *myVendorChannel;
    std::shared_ptr<BidFinishInfo> myBidFinishInfo;
    std::shared_ptr<BidReply> myVendorReply;   
    string productName;
    std::shared_ptr<Threadpool> tp_;
    blockingThreadpoolVendorCallerData(
            VendorClientChannel *vc,
            string prod,            
            std::shared_ptr<Threadpool> tp
        )
        :        
        myVendorChannel(vc),
        productName(prod),
        tp_(tp),
        my_thread_mutex()    
    {
        cout <<"thread callerdata locked"<<endl;
        my_thread_mutex.lock();//lock to indicate we job is created
    }
}blockingThreadpoolVendorCallerData;





//callback for threadpool to finish receiving data
void lockingThreadpoolVendorCallFinishRequest(void* data);


//callback for threadpool that calls into the assigned vendor 
void lockingThreadpoolVendorCallStartRequest(void* data);



class ServerImpl final {
 public:
  ~ServerImpl();

  ServerImpl(std::shared_ptr<Threadpool> tp ,vector<VendorClientChannel*> vcList);

  void Run(int port);
 private:
    std::shared_ptr<Threadpool> tp_;
    vector<VendorClientChannel*> vcList_;
  class StoreCallData {
   public:
    StoreCallData(Store::AsyncService* service, ServerCompletionQueue* cq,vector<VendorClientChannel*> vcList, std::shared_ptr<Threadpool> tpList);
        
    void Proceed();
   private:    
    vector<VendorClientChannel*> vcList_;
    std::shared_ptr<Threadpool> tp_;
    Store::AsyncService* service_;
    ServerCompletionQueue* cq_;
    ServerContext ctx_;
    ProductQuery request_;
    ProductReply reply_;
    ServerAsyncResponseWriter<ProductReply> responder_;
    enum CallStatus { CREATE, PROCESS, FINISH };
    CallStatus status_;
  };
  void HandleRpcs();
  std::unique_ptr<ServerCompletionQueue> cq_;
  Store::AsyncService service_;
  std::unique_ptr<Server> server_;
};


