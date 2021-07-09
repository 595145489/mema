#include "src/thread/ListenThread.h"
#include "src/base/Socket.h"
#include "src/FdChannel.h"
#include "src/poller/Poller.h"
#include "src/FdChannel.h"
#include "src/ThreadPool.h"
#include "src/ChannelList.h"
#include "src/base/Buffer.h"
#include "src/socketopt/SocketLink.h"
#include "src/socketopt/TcpConnection.h"
#include "src/socketopt/TcpAcceptor.h"

#include "src/thirdparty/gflags/include/gflags/gflags.h"

using namespace mema;

DECLARE_int32(PORT);
DECLARE_string(SERVERADDR);

ListenThread::ListenThread(std::shared_ptr<ThreadPool> pointer_poll,MemaBase* base_):create_flag(false),
                                                                                     poller_(Poller::GetDefaultPoller()),
                                                                                     pointer_poll(pointer_poll),
                                                                                     addr_(FLAGS_SERVERADDR.c_str()),
                                                                                     is_server(FLAGS_SERVERADDR=="0.0.0.0"?true:false),
                                                                                     port(FLAGS_PORT),
                                                                                     socket_link(is_server?
                                                                                                 dynamic_cast<SocketLink*>(new TcpAcceptor(this)):
                                                                                                 dynamic_cast<SocketLink*>(new TcpConnection(this))),
                                                                                     listen_channel(std::make_shared<FdChannel>(socket_link->GetSocketFd())),
                                                                                     list_buffer(std::make_shared<ListBuffer>(100)) { }

void ListenThread::Initialize()
{
    SetSocketReuseAddr(listen_channel);
    SetSocketReusePort(listen_channel);
    socket_link->CreateSocket(listen_channel.get(),addr_,port);
    socket_link->SetFdInitStatus(listen_channel);
    listen_channel->SetIndexModify();
    create_flag=true;
}


FdChannel* ListenThread::GetListenFd()
{
    return listen_channel.get();
}

void ListenThread::OnHandle()
{
    LOG_INFO("action handle");
    ChannelList activity_list;
    return ;
    for(;;){
        {
            std::shared_ptr<ThreadPool> temp = pointer_poll.lock();
            if(!temp || !temp->GetRunningStatus())
                break;
        }
        poller_->WaitActivity(activity_list);
        activity_list.ForEachThenRemove(
            bind(&SocketLink::HandleActivity,socket_link,std::placeholders::_1));
    };
}


void ListenThread::SetSocketReuseAddr(std::shared_ptr<FdChannel>& channel)
{
    Socket::SetSocketOpt<int>(channel->GetFd(),SO_REUSEADDR,1);
}

void ListenThread::SetSocketReusePort(std::shared_ptr<FdChannel>& channel)
{
    Socket::SetSocketOpt<int>(channel->GetFd(),SO_REUSEPORT,1); 
}

ListenThread::IovList ListenThread::GetIovec(int size)
{
    ListenThread::IovList iov(size);
    ListBuffer::Itertor iter(list_buffer);
    for(int count = 0;iter.Vaild() && size > count ;++count,iter.Next()){
        iov[count].iov_base = iter.Get()->begin();
        iov[count].iov_len  = iter.Get()->FreeSize();
    }
    return std::move(iov);
}

void ListenThread::OnRead(FdChannel* channel)
{
    LOG_INFO("begin read");
    ListenThread::IovList iov =  GetIovec(4);
    ssize_t size = Socket::Recdv(channel->GetFd(),&*(iov.begin()),4);
    ListBuffer::Itertor iter(list_buffer);
    ssize_t epoch_size = iter.Get()->GetMaxSize();
    int countofmessage = 0;
    do{
        if(!iter.Get()->SetSize(epoch_size>size?size:epoch_size))
            LOG_FATAL("no have enough size");
        size -= epoch_size;         
        ++countofmessage;
    }while(iter.Vaild() && size>0);
    std::shared_ptr<ListBuffer> message = std::make_shared<ListBuffer>(countofmessage,list_buffer);
    channel->UncompleteMessageCollectAndCompleteMessageDistribution(message,countofmessage,
                                                                    std::bind(&ListenThread::InsertCompleteMessage,this,std::placeholders::_1));
}

void ListenThread::InsertCompleteMessage(std::shared_ptr<ListBuffer>& message_buffer)
{
    unhandle_message.emplace_back(message_buffer);
}
void ListenThread::OnReadCallBackFunc(std::shared_ptr<ListBuffer>& message_buffer)
{
    /* list_buffer->EmplaceBackAndClear(message_buffer,message_buffer->GetTotalSize()); */
}

void ListenThread::OnWrite(FdChannel* channel)
{
    LOG_INFO("begin write");
    ListenThread::IovList iov =  GetIovec(4);
    ssize_t size = Socket::Writev(channel->GetFd(),&*(iov.begin()),4);
}

void ListenThread::OnConnection()
{
    auto addr_ipv6 = Socket::NewSockaddrIpv();
    std::shared_ptr<FdChannel> new_channel = std::make_shared<FdChannel>(Socket::AcceptFd(listen_channel->GetFd(),Socket::SocketaddrToSocketaddr6(addr_ipv6).get()));
    SetSocketReuseAddr(new_channel);
    SetSocketReusePort(new_channel);
    SetReadFd(new_channel);
    new_channel->SetIndexModify();
    new_channel->SetAddrIpv6(addr_ipv6);
    channel_list.emplace_back(new_channel);
}

void ListenThread::GetStatusAndSetUpdate(std::shared_ptr<FdChannel>& channel)
{
    poller_->update(channel->IsIndexNew()?poller_->AddFlagFd():poller_->ModflagFd(),
                    channel);
}

void ListenThread::SetReadFd(std::shared_ptr<FdChannel>& channel)
{
    channel->SetReadFd();
    GetStatusAndSetUpdate(channel);
}

void ListenThread::SetWriteFd(std::shared_ptr<FdChannel>& channel)
{
    channel->SetWriteFd();
    GetStatusAndSetUpdate(channel);
}

void ListenThread::SetWriteAndReadFd(std::shared_ptr<FdChannel> channel)
{
    channel->SetWriteAndReadFd();
    GetStatusAndSetUpdate(channel);
}

