#pragma once
#include "src/socketopt/SocketLink.h"

namespace mema{


class TcpConnection : public SocketLink
{
public:
    TcpConnection(ListenThread* thread);
    ~TcpConnection();

    void SetFdInitStatus(FdChannel* handle_fd) override;
    void CreateSocket(FdChannel* handle_fd,const char* addr_,int port) override;
    void HandleActivity(FdChannel* activity_fd) override;
private:
};

}// end namespace

