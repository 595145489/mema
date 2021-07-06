#include "src/poller/Poller.h"
#include "src/poller/EPoller.h"

using namespace mema;


Poller* Poller::GetDefaultPoller()
{
    return dynamic_cast<Poller*>(new EPoller()); 
}

