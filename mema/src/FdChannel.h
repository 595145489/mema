#pragma once
#include "src/base/Socket.h"
#include "src/base/MutexLock.h"
#include "src/base/WriteBuffer.h"

#include <functional>
#include <unordered_map>
#include <deque>

namespace mema{

class MemaBase;
class ListenThread;
class Epoller;
class ListBuffer;
class WriteBuffer;


enum class IndexStatus{
    KNew = 0,
    KMod = 1,
    KDle = 2
};

enum class SocketType{
    kNone = 0,
    kIPV4 = 1,
    kIPV6 = 2
};
class FdChannel
{

struct index_uncomplete{
    uint32_t total_size;
    std::shared_ptr<ListBuffer> message;
};



typedef std::unordered_map<uint32_t,index_uncomplete>  UncompleteMessage;
typedef std::function<void(std::shared_ptr<ListBuffer>& message)> ReadCallBack;

typedef std::deque<std::shared_ptr<WriteBuffer>>  UnwriteList;
/* friend class ListenThread; */
/* friend class Epoller; */
public:
    FdChannel(int fd_);
    ~FdChannel();

    int GetFd();
    bool IsReventRead(){return revent_ & kReadEvent;}
    bool IsReventWrite(){return revent_ & kWriteEvent;}
    bool IsIndexNew(){ return index==IndexStatus::KNew; }
    int Getevents(){ return event_; };

    void SetIndexModify(){ index = IndexStatus::KMod; }
    void SetIndexDelete(){ index = IndexStatus::KDle; }
    void SetIndexNew(){ index = IndexStatus::KNew; }
    void SetAddrIpv4(std::shared_ptr<sockaddr>& addr);
    void SetAddrIpv6(std::shared_ptr<sockaddr>& addr);

    void SetReadFd(){ event_ = kReadEvent;};
    void SetWriteFd(){event_ = kWriteEvent;};
    void SetWriteAndReadFd(){event_=kReadEvent|kWriteEvent;};
    void AddReadFd(){event_ |= kReadEvent;};
    void AddWriteFd(){event_ |= kWriteEvent;};
    void DelReadFd(){event_ ^= kReadEvent;};
    void DelWriteFd(){event_ ^= kWriteEvent;};
    void SetNoEventFd(){event_=kNoneEvent;};
    void SetRevent(int event){ revent_=event; };

    /* void OnRead(std::shared_ptr<ListBuffer>& message,ReadCallBack readcallbackfunc); */
    void UncompleteMessageCollectAndCompleteMessageDistribution(std::shared_ptr<ListBuffer>& message,int countofmessage,ReadCallBack readcallbackfunc);

    void Send(std::string &str);
private:
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    int socket_fd ;
    int event_;
    int revent_;
    IndexStatus index;
    std::shared_ptr<sockaddr> addr_ ;
    SocketType addr_type;
    uint32_t current_number;

    UnwriteList unwritelist GUARDED_BY(unwritelist_lock);
    MutexLock unwritelist_lock;
    // using for read message;
    UncompleteMessage uncomplete_message;

    MemaBase* base_;

};

}// end namespace

