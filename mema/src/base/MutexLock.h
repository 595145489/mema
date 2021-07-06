#pragma once
#include "src/base/noncopyable.h"

#include <pthread.h>

#if !defined(THREAD_ANNOTATION_ATTRIBUTE__)
#if defined(__clang__)
#define THREAD_ANNOTATION_ATTRIBUTE__(x) __attribute__((x))
#else
#define THREAD_ANNOTATION_ATTRIBUTE__(x)  // no-op
#endif
#endif  // !defined(THREAD_ANNOTATION_ATTRIBUTE__)

#ifndef GUARDED_BY
#define GUARDED_BY(x) THREAD_ANNOTATION_ATTRIBUTE__(guarded_by(x))
#endif

namespace mema{

class MutexLock:noncopyable
{
public:
    MutexLock();
    ~MutexLock();
    void Lock();
    void UnLock();
private:
    pthread_mutex_t mutex_;
};

class MutexLockGuard:noncopyable
{
public:
    MutexLockGuard(MutexLock&);
    ~MutexLockGuard();
private:
    MutexLock &owners;
};

}// end namespace

