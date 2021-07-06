#pragma once
#include "src/base/Log.h"

#include <arpa/inet.h>
#include <string>
#include <src/base/noncopyable.h>
#include <memory>


namespace mema{

class Socket:mema::noncopyable
{
public:

    // safe change
    template<typename sockaddr_type>
    static socklen_t GetSocketlen(sockaddr_type* addr_);
    static struct sockaddr* SocketaddrinToSocketaddr(struct sockaddr_in* addr_);
    static struct sockaddr_in* SocketaddrToSocketaddrin(struct sockaddr* addr_);
    static struct sockaddr_in6* SocketaddrToSocketaddrin6(struct sockaddr* addr_);
    static struct sockaddr* Socketaddrin6ToSocketaddr(struct sockaddr_in6* addr_);
    static struct sockaddr_in6* Socketaddrin6ToSocketaddrin(struct sockaddr_in* addr_);

    static std::shared_ptr<struct sockaddr> SocketaddrinToSocketaddr(std::shared_ptr<struct sockaddr_in> addr_);
    static std::shared_ptr<struct sockaddr_in> SocketaddrToSocketaddrin(std::shared_ptr<struct sockaddr> addr_);
    static std::shared_ptr<struct sockaddr> Socketaddrin6ToSocketaddr(std::shared_ptr<struct sockaddr_in6> addr_);
    static std::shared_ptr<struct sockaddr_in6> SocketaddrToSocketaddr6(std::shared_ptr<struct sockaddr> addr_);

    //in order to hide the struct of sockaddr
    static struct sockaddr_in GetSockaddrin();
    static struct sockaddr_in6 GetSockaddrin6();
    static std::shared_ptr<sockaddr> NewSockaddrIpv();
    static void GetLocalAddr(int fd,sockaddr_in6& addr_);
    static void GetLocalAddr(int fd,sockaddr_in& addr_);
    static void FromAddrToIp(const sockaddr* addr_,size_t addrlen,char* ip);

    static int GreateUdpSocketFd(sa_family_t family);
    static int GreateTcpSocketFd(sa_family_t family);
    static void SetSocketAddrIpv(struct sockaddr_in& addr_socket,
                                                    int port,
                                                    const char* ip = "0.0.0.0" );
    static void SetSocketAddrIpv(struct sockaddr_in6& addr_socket,
                                                    int port,
                                                    const char* ip = "0:0:0:0:0:0:0:0");
    static void BindFdToPort(const int fd,
                             const struct sockaddr* addr_); 
    static void ListenFd(const int fd);
    static int AcceptFd(const int fd,
                        struct sockaddr_in6* addr_);
    static int Connect(const int fd,
                       const struct sockaddr* addr_);
    static void CloseFd(int fd);
    static void Recvfrom(int sockfd, char* buffer, int buffer_len, struct sockaddr* from_addr_, unsigned int& from_len);
    static void SendTO(int sockfd, char* buffer, int buffer_len, struct sockaddr* to_addr_);

    static ssize_t Recdv(int sockfd, const struct iovec *iov,int iovcnt);
    static ssize_t Writev(int sockfd, const struct iovec *iov,int iovcnt);
    template<typename type>
    static void SetSocketOpt(int sockfd,int optname,type optval)
    {
        if(::setsockopt(sockfd,SOL_SOCKET,optname,&optval,sizeof(optval))){
            LOG_ERROR("set failure");
        }
    }
private:
    Socket();
    ~Socket();
    
};

}// end namespace

