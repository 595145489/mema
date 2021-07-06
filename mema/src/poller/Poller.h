#pragma once
#include <memory>

#ifndef POLLER_SIZE
    #define POLLER_SIZE 5000
#endif

namespace mema{

class FdChannel;
class ChannelList;

class Poller
{
public:
    Poller(){} ;
    virtual ~Poller(){} ;
    static Poller* GetDefaultPoller();
    virtual void update(int oeration,std::shared_ptr<FdChannel>& channel) = 0;
    virtual int WaitActivity(ChannelList &list_) = 0;
    virtual int AddFlagFd() = 0;
    virtual int ModflagFd() = 0;
    virtual int DelFlagFd() = 0;
    virtual void FillAcitivityChannelList(int ret,ChannelList &list_) = 0;
};

}// end namespace


