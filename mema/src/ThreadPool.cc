#include "src/ThreadPool.h"
#include "src/base/Log.h"
/* #include "src/thread/ListenThread.h" */
#include "src/MemoryPool.h"
#include "MemaBase.h"

using namespace mema;

std::atomic<bool> ThreadPool::running_status(false);

ThreadPool::ThreadPool(): 
                         memory_pool(new MemoryPool)
{
    uninitialized_thread.clear();
    count_thread.clear();
}

ThreadPool::~ThreadPool()
{
    count_thread.clear();

}
//new thread
void* ThreadPool::CreateThread(void* args)
{
    assert(args!=nullptr);
    //we do not delete handle_class in the this thread 
    //because it is the automatical pointer , we will delete it in the threadpool only.
    
    LOG_INFO("create thread_1 start");
    Thread* handle_class = static_cast<Thread*>(args);  
    handle_class->Initialize();
    handle_class->OnHandle();
    LOG_INFO("thread_1 end");
    return nullptr;
}

void ThreadPool::CreateAllThread()
{
    if(!GetRunningStatus())
        return;
    LOG_INFO("create thread start");
    for(auto &new_thread:uninitialized_thread)
        new_thread();
    LOG_INFO("create thread end");
    uninitialized_thread.clear();
}

void ThreadPool::WaitAllThread()
{
    
    for(auto &running_thread:count_thread){
        pthread_t pid = running_thread.first;
        ThreadBase::JoinThreadOne(pid);
    }
}

void ThreadPool::start()
{
    SetRunningStatus(true,std::memory_order_relaxed);
    CreateAllThread();

    WaitAllThread();
}

