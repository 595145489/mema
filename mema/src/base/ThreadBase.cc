#include "src/base/Log.h"
#include "src/base/ThreadBase.h"

using namespace mema;

pthread_t ThreadBase::CreateThread(void* (*func)(void*),void* args)
{
    pthread_t pthread_id;
    if(pthread_create(&pthread_id,NULL,func,args))
    {
        LOG_FATAL("create new thread failure");
    }
    return std::move(pthread_id);
}

void ThreadBase::DesdoryThread(pthread_t& pthread_id)
{
    pthread_detach(pthread_id);
}

void ThreadBase::JoinThreadOne(pthread_t& pthread_id)
{
    pthread_join(pthread_id,NULL);
}

void ThreadBase::CancelThreadOne(pthread_t& pthread_id)
{
    if(pthread_cancel(pthread_id)){
        LOG_FATAL("cancel thread failure");
    }
}

pthread_t ThreadBase::GetThreadId()
{
    return pthread_self();
}

