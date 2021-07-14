#pragma once
#include "src/socketopt/SocketLink.h"

namespace mema{

class TcpAcceptor :public SocketLink
{
public:
    TcpAcceptor(ListenThread *thread);
    ~TcpAcceptor();

    void SetFdInitStatus(FdChannel* handle_fd) override;
    void CreateSocket(FdChannel* handle_fd,const char* addr_,int port) override;
    void HandleActivity(FdChannel* activity_fd) override;
private:

};

}// end namespace

