#pragma once
#include "src/MemaBase.h"
#include "src/base/noncopyable.h"

#include <pthread.h>
#include <map>
#include <functional>
#include <memory>

namespace mema{

class ThreadPool;
class FdChannel;

class Thread 
{
public:
    Thread(){};
    virtual ~Thread(){};

    virtual void Initialize() = 0;
    virtual void OnHandle() = 0;
/* protected: */
/*     std::map<size_t,std::function<void()>> mapping_function; */
/*     std::weak_ptr<ThreadPool> pool_prt; */ 
};

}// end namespace

