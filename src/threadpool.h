#pragma once

#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <string>
using std::queue;
using std::thread;
using std::mutex;
using std::vector;

//a job to be processed by worker threads of threadpool
typedef struct job{
    //function pointer that will act upon the data*
    void (*action)(void*);
    //data to be acted upon by action
    void* data;
}Job;


class Threadpool {
private:
    //shutdown signal
    bool m_shutdown;    
    //thread pool
    vector<thread> m_pool;
    //protected job queue
    queue<std::shared_ptr<Job>> m_jbs;
    //mutex to protect the job queue
    mutex m_job_mutex;

    //function that runs in each worker thread that checks for new job requests
    static void infiniteLooper(Threadpool *tp);

    //create threads
    void createThreadqueue(int ct);

public:
    Threadpool(int threadCt);
    ~Threadpool();

    //adds a job to queue safely
    void addToJobQueue(std::shared_ptr<Job> jb);
  
};


