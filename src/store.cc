
#include "store.h"


std::shared_ptr<BidFinishInfo> VendorClientChannel::getProductBid(const std::string& product) {
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
std::shared_ptr<BidReply> VendorClientChannel::getVendorResult(std::shared_ptr<BidFinishInfo> bfi){ 
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




//callback for threadpool to finish receiving data
void lockingThreadpoolVendorCallFinishRequest(void* data){
    
        cout <<"finish request started"<<endl;
    blockingThreadpoolVendorCallerData* myThreadInfo= static_cast<blockingThreadpoolVendorCallerData*>(data);  

    myThreadInfo->myVendorReply= myThreadInfo->myVendorChannel->getVendorResult(myThreadInfo->myBidFinishInfo);
    myThreadInfo->my_thread_mutex.unlock();//unlock to indicate process is done


    
        cout <<"finish request done"<<endl;
}


//callback for threadpool that calls into the assigned vendor 
void lockingThreadpoolVendorCallStartRequest(void* data){

    
        cout <<"start request started"<<endl;
    blockingThreadpoolVendorCallerData* myThreadInfo= static_cast<blockingThreadpoolVendorCallerData*>(data);

    myThreadInfo->myBidFinishInfo= myThreadInfo->myVendorChannel->getProductBid(myThreadInfo->productName);

    //now we will place another job on queue to wait and finish my request
    
    shared_ptr<Job> jb(new Job);
    jb->action=&lockingThreadpoolVendorCallFinishRequest;
    jb->data=data;
    
    
        cout <<"added finish request"<<endl;

    //add to thread queue
    myThreadInfo->tp_->addToJobQueue(jb);
}




  ServerImpl::~ServerImpl() {
    server_->Shutdown();
    cq_->Shutdown();
  }

  ServerImpl::ServerImpl(std::shared_ptr<Threadpool> tp ,vector<VendorClientChannel*> vcList){
     tp_=tp;
    vcList_=vcList;
    }

  void ServerImpl::Run(int port) {
    std::string server_address("0.0.0.0:"+to_string(port));
    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service_);
    cq_ = builder.AddCompletionQueue();
    server_ = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;
    HandleRpcs();
  }
 


    ServerImpl::StoreCallData::StoreCallData(Store::AsyncService* service, ServerCompletionQueue* cq,vector<VendorClientChannel*> vcList, std::shared_ptr<Threadpool> tpList)
        : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE),vcList_(vcList),tp_(tpList) {
      Proceed();
    }

  void ServerImpl::HandleRpcs() {
    new StoreCallData(&service_, cq_.get(),vcList_,tp_);
    void* tag; 
    bool ok;
    while (true) {
      GPR_ASSERT(cq_->Next(&tag, &ok));
      GPR_ASSERT(ok);
      static_cast<StoreCallData*>(tag)->Proceed();
    }
  }

    void ServerImpl::StoreCallData::Proceed() {
      if (status_ == CREATE) {
        
        cout <<"creating"<<endl;
        status_ = PROCESS;
        service_->RequestgetProducts(&ctx_, &request_, &responder_, cq_, cq_,
                                  this);
      } else if (status_ == PROCESS) {
        
        cout <<"processing"<<endl;
        new StoreCallData(service_, cq_,vcList_,tp_);// allocate a new store call data to service more requests

        vector<shared_ptr<blockingThreadpoolVendorCallerData>> myPoolReq;
        vector<shared_ptr<Job>> myJobs;
        
        for(int i=0;i<vcList_.size();i++){
            //add requests to pool
            shared_ptr<blockingThreadpoolVendorCallerData> dt(new blockingThreadpoolVendorCallerData(vcList_[i],request_.product_name(),tp_));
            
            
            myPoolReq.push_back(dt);
            
        cout <<"setting data"<<endl;
            shared_ptr<Job> jb(new Job);
            jb->data=static_cast<void*>(dt.get()); 
            jb->action=&lockingThreadpoolVendorCallStartRequest;
            
            myJobs.push_back(jb);

            
            //add to q
            tp_->addToJobQueue(jb);
            
            
        }

    
        cout <<"now filling reply"<<endl;

        //now lets fill for our reply
        
        for(int i=0;i<myJobs.size();i++){

        //first block on thread data
        cout <<"trying to lock"<<endl;

        myPoolReq[i]->my_thread_mutex.lock();
        //wait till this lock gets unlocked after thread is done acting on it
        myPoolReq[i]->my_thread_mutex.unlock();
            
        
        cout <<"setting reply"<<endl;
        ProductInfo* pd= reply_.add_products();
        pd->set_price(myPoolReq[i]->myVendorReply->price());
        pd->set_vendor_id(myPoolReq[i]->myVendorReply->vendor_id());

        }

        
        cout <<"reaching finish"<<endl;
        status_ = FINISH;
        responder_.Finish(reply_, Status::OK, this);
      } else {
        GPR_ASSERT(status_ == FINISH);
        delete this;
      }
    }


Threadpool::Threadpool(int threadCt):m_shutdown(false),m_jbs(),m_pool(threadCt),m_job_mutex(){
        createThreadqueue(threadCt);
}


void Threadpool::infiniteLooper(Threadpool *tp){
        while(!tp->m_shutdown){
            shared_ptr<Job> myJob=NULL;
            tp->m_job_mutex.lock();
            //loops and checks for jobs
            if(tp->m_jbs.size()){
                myJob=tp->m_jbs.front();
                tp->m_jbs.pop();
            }
            tp->m_job_mutex.unlock();
            if(myJob){
                myJob->action(myJob->data);
            }
            else{
                sleep(0.1);
            }
        }
}

void Threadpool::createThreadqueue(int ct){
        

        for(int i=0;i<ct;i++){
            m_pool.push_back(thread(infiniteLooper,this));
        }


}

Threadpool::~Threadpool(){
        m_shutdown=true;
        for(auto & t : m_pool)
        {
            t.join();
        }
    }


void Threadpool::addToJobQueue(shared_ptr<Job> jb){
    m_job_mutex.lock();
    m_jbs.push(jb);
    m_job_mutex.unlock();
}


int main(int argc, char** argv) {

    if(argc<4){
        cout<<  "invalid arg count" << endl;
        return -1;
    }
    string fileName=string(argv[1]);
    int port=atoi(argv[2]);
    int threadCt=atoi(argv[3]);

    std::ifstream infile(fileName);


    vector<VendorClientChannel*> VendorClientChannelList;
    if (infile.is_open())
      {
      string line;
        while ( getline (infile,line) )
        {
            VendorClientChannelList.push_back(new VendorClientChannel(grpc::CreateChannel(
      line, grpc::InsecureChannelCredentials())));
        }
        infile.close();
      }

    
    std::shared_ptr<Threadpool> tp(new Threadpool(threadCt));

    ServerImpl server(tp,VendorClientChannelList);
    server.Run(port);                                                       

  return 0;
}
