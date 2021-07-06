#include "src/base/Socket.h" 
#include "src/base/Log.h"

#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/uio.h>

using namespace mema;

template<typename sockaddr_type>
socklen_t Socket::GetSocketlen(sockaddr_type* addr_)
{
    return std::move(static_cast<socklen_t>(sizeof(*addr_)));
}

struct sockaddr_in Socket::GetSockaddrin(){
    sockaddr_in addr_;
    memset(&addr_,0,sizeof(addr_));
    return std::move(addr_);
}

struct sockaddr_in6 Socket::GetSockaddrin6()
{
    sockaddr_in6 addr_;
    memset(&addr_,0,sizeof(addr_));
    return std::move(addr_);
}

std::shared_ptr<sockaddr> Socket::NewSockaddrIpv()
{
    std::shared_ptr<sockaddr_in6> addr_ (new sockaddr_in6());
    memset((addr_.get()),0,sizeof(sockaddr_in6));
    return Socket::Socketaddrin6ToSocketaddr(addr_);
}

void Socket::GetLocalAddr(int fd,sockaddr_in6& addr_)
{
    socklen_t addr_len = GetSocketlen<sockaddr_in6>(&addr_);
    if(::getsockname(fd,Socketaddrin6ToSocketaddr(&addr_),&addr_len)<0){
        LOG_ERROR("get socket addr failure");
    }
} 
void Socket::GetLocalAddr(int fd,sockaddr_in& addr_)
{
    socklen_t addr_len = GetSocketlen<sockaddr_in>(&addr_);
    if(::getsockname(fd,SocketaddrinToSocketaddr(&addr_),&addr_len)<0){
        LOG_ERROR("get socket addr failure");
    }
} 

void Socket::FromAddrToIp(const sockaddr* addr_,size_t addrlen,char* ip)
{
    if(::inet_ntop(addrlen>16?AF_INET6:AF_INET,addr_,ip,addrlen)==0)
    {
        LOG_ERROR("get ip failure");
    }
}

struct sockaddr* Socket::SocketaddrinToSocketaddr(struct sockaddr_in* addr_)
{
    return static_cast<struct sockaddr*>(static_cast<void*>(addr_));
}

struct sockaddr_in* Socket::SocketaddrToSocketaddrin(struct sockaddr* addr_)
{
    return static_cast<struct sockaddr_in*>(static_cast<void*>(addr_));
}

struct sockaddr* Socket::Socketaddrin6ToSocketaddr(struct sockaddr_in6* addr_)
{
    return static_cast<struct sockaddr*>(static_cast<void*>(addr_));
}

struct sockaddr_in6* Socket::SocketaddrToSocketaddrin6(struct sockaddr* addr_)
{
    return static_cast<struct sockaddr_in6*>(static_cast<void*>(addr_));
}

struct sockaddr_in6* Socket::Socketaddrin6ToSocketaddrin(struct sockaddr_in* addr_)
{
    return static_cast<struct sockaddr_in6*>(static_cast<void*>(addr_));
}

std::shared_ptr<struct sockaddr> Socket::SocketaddrinToSocketaddr(std::shared_ptr< struct sockaddr_in> addr_)
{
    return std::static_pointer_cast< struct sockaddr>(std::static_pointer_cast<void>(addr_));
}

std::shared_ptr<struct sockaddr_in> Socket::SocketaddrToSocketaddrin(std::shared_ptr<struct sockaddr> addr_)
{
    return std::static_pointer_cast<struct sockaddr_in>(std::static_pointer_cast<void>(addr_));
}

std::shared_ptr<struct sockaddr> Socket::Socketaddrin6ToSocketaddr(std::shared_ptr<struct sockaddr_in6> addr_)
{
    return std::static_pointer_cast<struct sockaddr>(std::static_pointer_cast<void>(addr_));
}

std::shared_ptr<struct sockaddr_in6> Socket::SocketaddrToSocketaddr6(std::shared_ptr< struct sockaddr> addr_)
{
    return std::static_pointer_cast<struct sockaddr_in6>(std::static_pointer_cast<void>(addr_));
}



int Socket::GreateUdpSocketFd(sa_family_t family)
{
    int socket_fd = ::socket(family,SOCK_DGRAM,IPPROTO_UDP);
    if(socket_fd<0){
        LOG_ERROR("create udp socket failure");
    }
    return socket_fd;
}

int Socket::GreateTcpSocketFd(sa_family_t family)
{
    int socket_fd = ::socket(family,SOCK_STREAM,IPPROTO_TCP);
    if(socket_fd<0){
        LOG_ERROR("create tcp socket failure");
    }
    return socket_fd;
}


void Socket::SetSocketAddrIpv(struct sockaddr_in& addr_socket,
                                                 int port,
                                                 const char* ip)
{
    addr_socket.sin_family = AF_INET;
    addr_socket.sin_port = htons(port);
    if(::inet_pton(AF_INET,ip,&addr_socket.sin_addr.s_addr)==0){
        LOG_ERROR("inet_poton ipv4 failure");
    }
}

void Socket::SetSocketAddrIpv(struct sockaddr_in6& addr_socket,
                                                 int port,
                                                 const char* ip)
{
    memset(&addr_socket,0,static_cast<socklen_t>(sizeof(addr_socket)));
    addr_socket.sin6_family = AF_INET6;
    addr_socket.sin6_port = htons(port);
    if(::inet_pton(AF_INET6,ip,&addr_socket.sin6_addr)==0){
        LOG_ERROR("inet_poton ipv6 failure");
    }
}

void Socket::BindFdToPort(const int fd,
                          const struct sockaddr* addr_)
{
    int ret = ::bind(fd,addr_,static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
    if(ret<0){
        LOG_ERROR("bind socket failure");
    }
}

void Socket::ListenFd(const int fd)
{
    int ret = ::listen(fd,SOMAXCONN);
    if(ret<0){
        LOG_ERROR("listen socket failure");
    }
} 
int Socket::AcceptFd(const int fd,struct sockaddr_in6* addr_)
{
    socklen_t addr_len = Socket::GetSocketlen<sockaddr_in6>(addr_);
    int connfd = ::accept4(fd,
                        Socket::Socketaddrin6ToSocketaddr(addr_),
                        &addr_len, 
                        SOCK_NONBLOCK |SOCK_CLOEXEC);
    if(connfd<0){
        LOG_ERROR("accept socket failure");
    }
    return connfd;
}

int Socket::Connect(const int fd,const struct sockaddr* addr_)
{
    return ::connect(fd,
                    addr_,
                    static_cast<socklen_t>(sizeof(struct sockaddr_in6*)));
}

void Socket::CloseFd(int fd)
{ 
    int ret = ::close(fd);
    if(ret<0){
        LOG_ERROR("close socket failure");
    }
}


void Socket::Recvfrom(int sockfd, char* buffer, int buffer_len, struct sockaddr* from_addr_, unsigned int& from_len)
{
    int ret = ::recvfrom(sockfd,
                         buffer,
                         buffer_len,
                         0,
                         from_addr_,
                         &from_len);
    if(ret < 0){
        LOG_ERROR("recv socket failure");
    }
}

void Socket::SendTO(int sockfd, char* buffer, int buffer_len, struct sockaddr* to_addr_)
{
    int ret = ::sendto(sockfd,
                       buffer,
                       buffer_len,
                       0,
                       to_addr_,
                       static_cast<socklen_t>(sizeof(struct sockaddr_in6)));
    if(ret < 0){
        LOG_ERROR("recv socket failure");
    }

}

ssize_t Socket::Recdv(int sockfd, const struct iovec *iov,int iovcnt)
{
    return ::readv(sockfd,iov,iovcnt);
}

ssize_t Socket::Writev(int sockfd, const struct iovec *iov,int iovcnt)
{
    return ::writev(sockfd,iov,iovcnt);
}


