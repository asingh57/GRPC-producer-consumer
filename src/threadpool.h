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
typedef struct job{
    void (*action)(void*);
    void* data;
}Job;
class Threadpool {
private:
    bool m_shutdown;    
    vector<thread> m_pool;
    queue<std::shared_ptr<Job>> m_jbs;
    mutex m_job_mutex;

    static void infiniteLooper(Threadpool *tp);

    void createThreadqueue(int ct);

public:
    Threadpool(int threadCt);
    ~Threadpool();

    void addToJobQueue(std::shared_ptr<Job> jb);
  
};


