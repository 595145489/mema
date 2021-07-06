#include "src/base/Socket.h"
#include "src/base/Log.h"
using namespace mema;

#include <iostream>

 int main(){


    sockaddr_in addr_ipv4 ;
    Socket::SetSocketAddrIpv(addr_ipv4,6002);
    int fd = Socket::GreateTcpSocketFd(AF_INET); 
    Socket::BindFdToPort(fd,Socket::SocketaddrinToSocketaddr(&addr_ipv4));
    Socket::ListenFd(fd);
    while(1){
       sockaddr_in aa;   
    int new_s =  Socket::AcceptFd(fd,Socket::Socketaddrin6ToSocketaddrin(&aa));
    std::cout << new_s << std::endl;
    char buff[512] = {0};
    struct iovec cache[1];
    cache[0].iov_base = buff;
    cache[0].iov_len = sizeof(buff)+1;
    int ss = Socket::Recdv(new_s,cache,1);
    std::cout << ss << std::endl;
    std::cout << buff << std::endl;
    LOG_INFO(ss);
    LOG_INFO(buff);
    }

    

    //untest
    sockaddr_in6 addr_ipv6;
    Socket::SetSocketAddrIpv(addr_ipv6,6002);
    int fd6 = Socket::GreateUdpSocketFd(AF_INET6); 
    Socket::BindFdToPort(fd6,Socket::Socketaddrin6ToSocketaddr(&addr_ipv6));


    char buffer[512] = "123123";
    sockaddr_in send_addr_;
    Socket::SetSocketAddrIpv(send_addr_,6001,"192.168.1.176");
    int sfd = Socket::GreateUdpSocketFd(AF_INET); 
    Socket::SendTO(sfd,buffer,7,Socket::SocketaddrinToSocketaddr(&send_addr_));


    sockaddr addr_ip;
    unsigned int addr_len;
    sockaddr_in addr_ipv ;
    Socket::Recvfrom(fd,buffer,512,&addr_ip,addr_len);

    Socket::GetLocalAddr(fd,addr_ipv);
    LOG_DEBUG(buffer);
    char ip[20];
    Socket::FromAddrToIp(&addr_ip,addr_len,ip);
    LOG_INFO(ip);

    return 0;

}


