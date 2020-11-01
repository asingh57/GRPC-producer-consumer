 
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

//take commonly used structures from namespace
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


//contains information about a particular bid made to a particular vendor
typedef struct bidFinishInfo{
    std::shared_ptr<ClientAsyncResponseReader<BidReply>> rpc;
    std::shared_ptr<CompletionQueue> cq;
    std::shared_ptr<ClientContext> ctx;
    std::shared_ptr<BidReply> vr;
    std::shared_ptr<Status> st;
} BidFinishInfo;




//This is the store's "client" to a single vendor
class VendorClientChannel {
 public:
    //initialise a channel to a particular vendor
  explicit VendorClientChannel(std::shared_ptr<Channel> channel)
      : stub_(Vendor::NewStub(channel)) {}

    //starts product bid request from vendor asynchronously
   std::shared_ptr<BidFinishInfo> getProductBid(const std::string& product);

    //collects result of product bid request
    std::shared_ptr<BidReply> getVendorResult(std::shared_ptr<BidFinishInfo> bfi);

 private:
    //stub we use at the vendor
  std::unique_ptr<Vendor::Stub> stub_;
};


//data structure to be passed to the function callback of a threadpool job
//it includes everything for a thread to make requests to a vendor
typedef struct blockingThreadpoolVendorCallerData{
    mutex my_thread_mutex;//blocks until this request is done serving
    VendorClientChannel *myVendorChannel;//channel to the vendor
    std::shared_ptr<BidFinishInfo> myBidFinishInfo;//data structure to store bid information
    std::shared_ptr<BidReply> myVendorReply;//data structure to store the bid reply 
    string productName;//product name to query
    std::shared_ptr<Threadpool> tp_;//pointer to thread pool
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


//Store server that runs on a specific port
class ServerImpl final {
 public:
    //handle server closure cleanly
  ~ServerImpl();

    //initialise with a thread pool and a list of vendor channels
  ServerImpl(std::shared_ptr<Threadpool> tp ,vector<VendorClientChannel*> vcList);

    //server runner
  void Run(int port);
 private:
    //private threadpool for the server
    std::shared_ptr<Threadpool> tp_;
    //list of vendors channels associated with the service
    vector<VendorClientChannel*> vcList_;
  
  void HandleRpcs();
  std::unique_ptr<ServerCompletionQueue> cq_;
  Store::AsyncService service_;
  std::unique_ptr<Server> server_;


//subclass data structure that services a particular call into the store
  class StoreCallData {
   public:

    StoreCallData(Store::AsyncService* service, ServerCompletionQueue* cq,vector<VendorClientChannel*> vcList, std::shared_ptr<Threadpool> tpList);
    //continue with call servicing
    void Proceed();
   private:    
    vector<VendorClientChannel*> vcList_;
    std::shared_ptr<Threadpool> tp_;
    Store::AsyncService* service_;//asynchronous service provided by the handler
    ServerCompletionQueue* cq_;//queue of the server
    ServerContext ctx_;//context of the server for the particular request
    ProductQuery request_; //request recieved
    ProductReply reply_;//request reply being filled
    ServerAsyncResponseWriter<ProductReply> responder_;//async responder to the client
    enum CallStatus { CREATE, PROCESS, FINISH };
    CallStatus status_;
  };
};


