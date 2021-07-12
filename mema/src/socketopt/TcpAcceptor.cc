#include "src/socketopt/TcpAcceptor.h"
#include "src/socketopt/SocketLink.h"
#include "src/base/Socket.h"
#include "src/FdChannel.h"
#include "src/thread/ListenThread.h"

using namespace mema;

TcpAcceptor::TcpAcceptor(ListenThread *thread):SocketLink(thread)
{

}

TcpAcceptor::~TcpAcceptor()
{

}

void TcpAcceptor::SetFdInitStatus(std::shared_ptr<FdChannel> handle_fd)
{
    handle_fd->SetReadFd();
}

void TcpAcceptor::CreateSocket(FdChannel* handle_fd,const char* addr_,int port)
{
    auto addr_ipv4 = Socket::NewSockaddrIpv();
    Socket::SetSocketAddrIpv(*(Socket::SocketaddrToSocketaddrin(addr_ipv4).get()),port,addr_);
    Socket::BindFdToPort(handle_fd->GetFd(),addr_ipv4.get());
    Socket::ListenFd(handle_fd->GetFd());
    handle_fd->SetAddrIpv4(addr_ipv4);
}

void TcpAcceptor::HandleActivity(FdChannel* activity_fd)
{
    if(activity_fd==listten_thread->GetListenFd()){
        listten_thread->OnConnection();
    }
    else if(activity_fd->IsReventRead()){
        listten_thread->OnRead(activity_fd);
    }
    else if(activity_fd->IsReventWrite()){
        listten_thread->OnWrite(activity_fd);
    }
}

