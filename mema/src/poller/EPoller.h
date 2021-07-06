#pragma once
#include "src/poller/Poller.h"

#include <memory>
#include <sys/epoll.h>
#include <vector>

namespace mema{

class FdChannel;

class EPoller:public Poller
{
typedef std::vector<epoll_event> EventList;
public:
    EPoller();
    ~EPoller();
    void update(int operation,std::shared_ptr<FdChannel>& channel) override;
    int WaitActivity(ChannelList &list_) override;

    int AddFlagFd() override {return EPOLL_CTL_ADD;};
    int ModflagFd() override {return EPOLL_CTL_MOD;};
    int DelFlagFd() override {return EPOLL_CTL_DEL;};
    void FillAcitivityChannelList(int ret,ChannelList &list_) override;
private:
    void SetEpollEvent();
    void SetReadPoll();
    void SetWritePoll();
    void SetWriteAndReadPoll();
    void SetNoEventPoll();
private:
    int epoll_fd;
    struct epoll_event event_;
    EventList events;
};

}// end namespace

