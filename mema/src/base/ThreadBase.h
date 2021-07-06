#pragma once
#include "src/base/noncopyable.h"

#include <pthread.h>
namespace mema{

class ThreadBase:noncopyable
{
public:
    static pthread_t CreateThread(void* (*func)(void*),void* args);
    static void DesdoryThread(pthread_t& pthread_id);
    static void JoinThreadOne(pthread_t& pthread_id);
    static void CancelThreadOne(pthread_t& pthread_id);
    static pthread_t GetThreadId();

    //todo
    static void JoinThreadAll();
private:
    ThreadBase() = delete;
    ~ThreadBase() = delete;
};

}// end namespace

