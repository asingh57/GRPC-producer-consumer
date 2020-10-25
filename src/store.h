 
#include "threadpool.h"

//NOTE: Part of implementation is taken from hello world async example on grpc github

#include <fstream>

#include <grpc++/grpc++.h>
#include <string>
#include "vendor.grpc.pb.h"
#include "vendor.pb.h"
#include "store.grpc.pb.h"
#include "store.pb.h"
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
