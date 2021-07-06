#pragma once
#include "src/base/MutexLock.h"
#include "src/base/ThreadBase.h"
#include "src/thread/Thread.h"
#include "src/thread/ListenThread.h"

#include <type_traits>
#include <map>
#include <atomic>
#include <pthread.h>
#include <memory>
#include <functional>
#include <deque>
#include <assert.h>
#include <mutex>

#define LOOPTIME(numberofloop,func) for(int count = 0;count<numberofloop;count++){func}

namespace mema{

class MemoryPool;
class MemaBase;
class MutexLock;

class ThreadPool: public  std::enable_shared_from_this<ThreadPool>
{
typedef std::function<void()> ThreadFunc;
typedef std::function<void()> DelayFunc;
public:
    ThreadPool();
    ~ThreadPool();
    inline bool GetRunningStatus(){
        return running_status.load(std::memory_order_acquire);
    };
    inline void SetRunningStatus(bool status,std::memory_order order){
        running_status.store(status,order);
    };
    void DesdoryThreadOne();
    void start();
private:
    static void* CreateThread(void* args);
    void CreateAllThread();
    void WaitAllThread();
private:
    /* std::unique_ptr<Control> dispath_thread; */
    std::unique_ptr<MemoryPool> memory_pool;
    static std::atomic<bool> running_status;

    MutexLock mutex_;
    std::deque<DelayFunc> uninitialized_thread; //thread unsafe
    std::deque<int> uninitialized_int ; //thread unsafe
    //Do not change the thread pointer.
    //The modification is only in the function to delete it, which we must to make sure that the thread who used it has been destroy;
    std::map<pthread_t,std::shared_ptr<Thread>> count_thread; 
private:
    template <typename threadclass,
              typename std::enable_if<std::is_base_of<Thread,threadclass>::value,int>::type = 1>
    void GreateDelayThread(MemaBase* handleclass){
        std::shared_ptr<Thread> thread_class = std::make_shared<threadclass>(shared_from_this(),handleclass);
        pthread_t pid = ThreadBase::CreateThread(&ThreadPool::CreateThread,static_cast<void*>(thread_class.get()));
        count_thread[pid] = thread_class;
    };
public:
    template <typename threadclass,
              typename std::enable_if<std::is_base_of<Thread,threadclass>::value,int>::type = 1>
    void AddNewThread(MemaBase* handleclass,int numberofloop){
        LOOPTIME(numberofloop,
            if(!this->GetRunningStatus()){
                //we do not to lock here ,because there just have one thread.
                uninitialized_thread.push_back(std::bind(&ThreadPool::GreateDelayThread<threadclass>,this,handleclass)); 
            }
        )

    };
};

}// end namespace

