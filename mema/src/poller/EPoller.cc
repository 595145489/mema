#include "src/poller/EPoller.h" 
#include "src/FdChannel.h"
#include "src/base/Log.h"
#include "src/ChannelList.h"

#include <sys/poll.h>
#include <stdio.h>
#include <unistd.h>

#define DEFAULT_EVENT_SIZE 20

using namespace mema;
// On Linux, the constants of poll(2) and epoll(4)
// are expected to be the same.
static_assert(EPOLLIN == POLLIN,        "epoll uses same flag values as poll");
static_assert(EPOLLPRI == POLLPRI,      "epoll uses same flag values as poll");
static_assert(EPOLLOUT == POLLOUT,      "epoll uses same flag values as poll");
static_assert(EPOLLRDHUP == POLLRDHUP,  "epoll uses same flag values as poll");
static_assert(EPOLLERR == POLLERR,      "epoll uses same flag values as poll");
static_assert(EPOLLHUP == POLLHUP,      "epoll uses same flag values as poll");



EPoller::EPoller():epoll_fd(::epoll_create1(EPOLL_CLOEXEC)),
                   events(DEFAULT_EVENT_SIZE)
{
    SetEpollEvent();
    LOG_INFO("create epoll");
}

EPoller::~EPoller()
{
    ::close(epoll_fd);
}

void EPoller::SetEpollEvent()
{
    event_.data.fd= epoll_fd;
    SetReadPoll();
}

void EPoller::SetReadPoll()
{
    event_.events = EPOLLIN|EPOLLPRI; 
}

void EPoller::SetWritePoll()
{
    event_.events = EPOLLOUT; 
}

void EPoller::SetWriteAndReadPoll()
{
    event_.events = EPOLLIN|EPOLLPRI|EPOLLOUT; 
}

void EPoller::SetNoEventPoll()
{
    event_.events = 0;
}

void EPoller::update(int operation,std::shared_ptr<FdChannel>& channel)
{
    struct epoll_event event;
    int fd = channel->GetFd();
    LOG_INFO("update channel fd = " << fd);
    event.events = channel->Getevents();
    event.data.ptr = channel.get();
    if(::epoll_ctl(epoll_fd,operation,fd,&event)){
        LOG_FATAL("Update epollfd:" << epoll_fd << " failure, fd number:" << fd << "errno code:" << errno);
    }
}

int EPoller::WaitActivity(ChannelList &list_)
{
    int ret = ::epoll_wait(epoll_fd,&*events.begin(),POLLER_SIZE,-1); 
    FillAcitivityChannelList(ret,list_);
    return std::move(ret);
}

void EPoller::FillAcitivityChannelList(int ret,ChannelList &list_)
{
    for(int activity_fd = 0;activity_fd<ret;++activity_fd){
        //we must to make sure that the tmp had not been removed
        FdChannel* tmp = static_cast<FdChannel*> (events[activity_fd].data.ptr);
        tmp->SetRevent(events[activity_fd].events);
        list_.PushBack(tmp);
    }
}

