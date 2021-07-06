#include "src/base/MutexLock.h"

using namespace mema;

MutexLock::MutexLock()
{
    pthread_mutex_init(&mutex_,NULL);
}

MutexLock::~MutexLock()
{
    pthread_mutex_destroy(&mutex_);
}

void MutexLock::Lock()
{
    pthread_mutex_lock(&mutex_);
}

void MutexLock::UnLock()
{
    pthread_mutex_unlock(&mutex_);
}


MutexLockGuard::MutexLockGuard(MutexLock& owners):owners(owners)
{
    owners.Lock();
}

MutexLockGuard::~MutexLockGuard()
{
    owners.UnLock();
}



