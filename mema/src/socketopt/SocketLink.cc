#include "src/socketopt/SocketLink.h"
#include "src/base/Socket.h"

using namespace mema;

SocketLink::SocketLink(ListenThread* thread):listten_thread(thread)
{

}

SocketLink::~SocketLink() 
{

}

int SocketLink::GetSocketFd() {
    return Socket::GreateTcpSocketFd(AF_INET);
};
