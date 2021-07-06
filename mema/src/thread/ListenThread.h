#pragma once
#include "src/thread/Thread.h"
#include "src/base/ListBuffer.h"

#include <memory>
#include <vector>
#include <fcntl.h>

namespace mema{

class MemaBase;
class FdChannel;
class Poller;
class ChannelList;

class ListenThread :public Thread
{
typedef std::vector<std::shared_ptr<FdChannel>> ChannelSave;
typedef std::vector<struct iovec> IovList; 
public:
    ListenThread(std::shared_ptr<ThreadPool> pointer_poll,MemaBase* base_);
    ~ListenThread() {};

    void CreateSocket(int port);
    void Initialize() override;
    void OnHandle() override;

    void SetReadFd(std::shared_ptr<FdChannel>& channel);
    void SetWriteFd(std::shared_ptr<FdChannel>& channel);
    void SetWriteAndReadFd(std::shared_ptr<FdChannel> channel);
private:
    void SetSocketReuseAddr(std::shared_ptr<FdChannel>& channel);
    void SetSocketReusePort(std::shared_ptr<FdChannel>& channel);
    void HandleActivity(FdChannel* activity_fd);
    void GetStatusAndSetUpdate(std::shared_ptr<FdChannel>& channel);

    IovList GetIovec(int size); 
    void OnConnection();
    void OnRead(FdChannel* channel);
    void OnWrite(FdChannel* channel);

    void OnReadCallBackFunc(std::shared_ptr<ListBuffer>& message_buffer);
    void InsertCompleteMessage(std::shared_ptr<ListBuffer>& message_buffer);
private:
    bool create_flag;
    std::shared_ptr<Poller> poller_;
    std::weak_ptr<ThreadPool> pointer_poll;
    int port;
    std::shared_ptr<FdChannel> listen_channel;
    std::shared_ptr<ListBuffer> list_buffer; 
    ChannelSave channel_list;
    std::vector<std::shared_ptr<ListBuffer>> unhandle_message;
};

}// end namespace
