#pragma once
#include "src/thread/Thread.h"
#include "src/base/ListBuffer.h"

#include <memory>
#include <vector>
#include <set>
#include <fcntl.h>

namespace mema{

class MemaBase;
class FdChannel;
class Poller;
class ChannelList;
class SocketLink;

class ListenThread :public Thread
{
typedef std::map<int,std::shared_ptr<FdChannel>> ChannelSave;
typedef std::vector<struct iovec> IovList; 
public:
    ListenThread(std::shared_ptr<ThreadPool> pointer_poll,MemaBase* base_);
    ~ListenThread() {};

    /* void CreateSocket(int port); */
    void Initialize() override;
    void OnHandle() override;


    void OnConnection();
    void OnRead(FdChannel* channel);
    void OnWrite(FdChannel* channel);
    void OnClose(FdChannel* channel);

    void ReadCompleteMessage();
    FdChannel* GetListenFd();
    void CloseRunning();
private:
    void SetSocketReuseAddr(std::shared_ptr<FdChannel>& channel);
    void SetSocketReusePort(std::shared_ptr<FdChannel>& channel);
    /* void HandleActivity(FdChannel* activity_fd); */
    void GetStatusAndSetUpdate(FdChannel* channel);

    IovList GetIovec(int size,std::shared_ptr<ListBuffer>& list_); 

    void OnReadCallBackFunc(std::shared_ptr<ListBuffer> message_buffer);
    void InsertCompleteMessage(FdChannel* fd,std::shared_ptr<ListBuffer>& message_buffer);
private:
    bool create_flag;
    MemaBase* base_;
    std::shared_ptr<Poller> poller_;
    std::weak_ptr<ThreadPool> pointer_poll;
    const char* addr_;
    bool is_server;
    int port;
    std::shared_ptr<SocketLink> socket_link;
    std::shared_ptr<FdChannel> listen_channel;
    std::shared_ptr<ListBuffer> list_buffer; 
    ChannelSave channel_list;
    std::vector<std::pair<FdChannel*,std::shared_ptr<ListBuffer>>> unhandle_message;
};

}// end namespace

