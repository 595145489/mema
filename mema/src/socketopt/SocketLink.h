#pragma once
#include "src/base/noncopyable.h"

#include <memory>

namespace mema{

class FdChannel;
class ListenThread;

class SocketLink 
{
public:
    SocketLink(ListenThread* thread);
    virtual ~SocketLink(); 

    virtual int GetSocketFd() ;
    virtual void SetFdInitStatus(std::shared_ptr<FdChannel> handle_fd) = 0;
    virtual void CreateSocket(FdChannel* handle_fd,const char* addr_,int port) = 0;
    virtual void HandleActivity(FdChannel* activity_fd) = 0;
protected:
    ListenThread* listten_thread;
};

}// end namespace

