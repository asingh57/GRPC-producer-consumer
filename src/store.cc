
#include "store.h"
#include <grpc++/grpc++.h>

#include "vendor.grpc.pb.h"
#include "vendor.pb.h"

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

class VendorClient {
 public:
  explicit VendorClient(std::shared_ptr<Channel> channel)
      : stub_(Vendor::NewStub(channel)) {}

   std::shared_ptr<BidFinishInfo> getProductBid(const std::string& product) {

    
    BidQuery request;
    request.set_product_name(product);

    std::shared_ptr<ClientContext> ctx=std::shared_ptr<ClientContext>(new ClientContext);
    std::shared_ptr<CompletionQueue> cq=std::shared_ptr<CompletionQueue>(new CompletionQueue);

    std::shared_ptr<ClientAsyncResponseReader<BidReply> > rpc(
        stub_->AsyncgetProductBid(ctx.get(), request, cq.get()));

    

    std::shared_ptr<BidReply> vr=  std::shared_ptr<BidReply>(new BidReply);
    std::shared_ptr<Status> st=  std::shared_ptr<Status>(new Status);

    rpc->Finish(vr.get(), st.get(), (void*)1);


    std::shared_ptr<BidFinishInfo> finInf=std::shared_ptr<BidFinishInfo>(new BidFinishInfo);

    finInf->vr=vr;
    finInf->st=st;
    finInf->cq=cq;
    finInf->rpc=rpc;
    finInf->ctx=ctx;
    
    
    return finInf;
  }

    std::shared_ptr<BidReply> getVendorResult(std::shared_ptr<BidFinishInfo> bfi){ 

        
        void* got_tag;
        bool ok = false;
        //block here
        GPR_ASSERT(bfi->cq->Next(&got_tag, &ok));
        GPR_ASSERT(got_tag == (void*)1);
        GPR_ASSERT(ok);
        if (bfi->st->ok()) {
        } else {
            cout<< "error, getProductBid failed";
        }
        return bfi->vr;
    }

 private:
  std::unique_ptr<Vendor::Stub> stub_;
};
int main(int argc, char** argv) {
  VendorClient client(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));

  std::string product("trimmer");
    
  std::shared_ptr<BidFinishInfo> bf = client.getProductBid(product);
    
    
    std::shared_ptr<BidReply> br= client.getVendorResult(bf);


  std::cout << "Store received: " << br->price() << "from"<< br->vendor_id() << std::endl;
  return 0;
}
