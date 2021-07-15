#include "src/socketopt/SocketLink.h"
#include "src/socketopt/TcpConnection.h"
#include "src/base/Socket.h"
#include "src/FdChannel.h"
#include "src/thread/ListenThread.h"

using namespace mema;
TcpConnection::TcpConnection(ListenThread* thread):SocketLink(thread)
{

}

TcpConnection::~TcpConnection()
{

}

void TcpConnection::SetFdInitStatus(FdChannel* handle_fd)
{
    handle_fd->SetReadFd();
}

void TcpConnection::CreateSocket(FdChannel* handle_fd,const char* addr_,int port)
{
    auto addr_ipv4 = Socket::NewSockaddrIpv();
    Socket::SetSocketAddrIpv(*(Socket::SocketaddrToSocketaddrin(addr_ipv4).get()),port,addr_);
    Socket::Connect(handle_fd->GetFd(),addr_ipv4.get());
    handle_fd->SetAddrIpv4(addr_ipv4);
    SetFdInitStatus(handle_fd);
    handle_fd->SetIndexModify();
    handle_fd->OnConnection();
}

void TcpConnection::HandleActivity(FdChannel* activity_fd)
{
    if(activity_fd->IsReventRead()){
        listten_thread->OnRead(activity_fd);
    }
    else if(activity_fd->IsReventWrite()){
        listten_thread->OnWrite(activity_fd);
    }
}

void TcpConnection::CloseFd(FdChannel* activity_fd)
{
    Socket::CloseFd(activity_fd->GetFd());
    listten_thread->CloseRunning();
    listten_thread->OnClose(activity_fd);
}

