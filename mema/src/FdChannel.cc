#include "src/FdChannel.h"
#include "src/base/ListBuffer.h"
#include "src/base/coding.h"

#include "sys/poll.h"
#include <fcntl.h>


using namespace mema;

const int FdChannel::kNoneEvent = 0;
const int FdChannel::kReadEvent = POLLIN | POLLPRI;
const int FdChannel::kWriteEvent = POLLOUT;


FdChannel::FdChannel(int fd_):socket_fd(fd_),
                              event_(kNoneEvent),
                              revent_(kNoneEvent),
                              index(IndexStatus::KNew),
                              addr_(nullptr),
                              addr_type(SocketType::kNone),
                              current_number(1) { }

void FdChannel::SetAddrIpv4(std::shared_ptr<sockaddr>& addr)
{
    addr_type = SocketType::kIPV4;
    addr_ = addr;
}

void FdChannel::SetAddrIpv6(std::shared_ptr<sockaddr>& addr)
{
    addr_type = SocketType::kIPV6;
    addr_ = addr;
}


FdChannel::~FdChannel()
{

}

int FdChannel::GetFd()
{
    return socket_fd;
}


// first four char (first number is 1) are number then nest four char are the index of number .
// if the index of number is the first flag that equal to 1 and should be take the count of number's messgae ;
void FdChannel::UncompleteMessageCollectAndCompleteMessageDistribution(std::shared_ptr<ListBuffer>& message,int countofmessage,ReadCallBack readcallbackfunc)
{ 
    const static uint32_t NotFirstRequest = 0;
    const static uint32_t FirstRequestFlag = 12336;

    ListBuffer::Itertor iter(message); 

    std::function<const char*()> GetHeaderNumber = [&]()-> const char *{
        auto local = reinterpret_cast<const char*>(iter.Get()->IterPosition());
        iter.Get()->Seek(4);
        return local; 
    };
    std::function<const char*()> GetHeaderIndex = [&]()-> const char *{
        auto local = reinterpret_cast<const char*>(iter.Get()->IterPosition());
        iter.Get()->Seek(4);
        return local; 
    };
    std::function<const char*()>GetHeaderCountof = [&]()-> const char *{
        auto local = reinterpret_cast<const char*>(iter.Get()->IterPosition());
        iter.Get()->Seek(4);
        return local; 
    };
    uint32_t cache_number, cache_index, cache_number_of_all_message;
    uint32_t number = mema::DecodeFixd32(GetHeaderNumber());
    uint32_t countofallmessage = 1;


   auto VariableSet = [&](){
        cache_number = number;
        cache_index =  mema::DecodeFixd32(GetHeaderIndex());
        cache_number_of_all_message = FirstRequestFlag == cache_index?mema::DecodeFixd32(GetHeaderCountof()):NotFirstRequest;
        countofmessage = 1;
        iter.Next();
    };
    auto MessagePass = [&](){
        //the message is uncomplete and restore in the unordered_map
        if(cache_number_of_all_message==NotFirstRequest)
        {
            auto index_message = uncomplete_message.find(cache_number);
            if(index_message==uncomplete_message.end()){
                LOG_FATAL("uncomplete message");
                return;
            }
            index_message->second.message->EmplaceBack(message,countofallmessage);
            // if message has been completed , pass it to the readcallback
            if(index_message->second.total_size == cache_index){
                readcallbackfunc(index_message->second.message);
                uncomplete_message.erase(index_message);
            }
        }
        // the message is complete and all the message in this message buffer;
        else if(cache_number_of_all_message == cache_index){ 
            std::shared_ptr<ListBuffer> complete_message = std::make_shared<ListBuffer>(countofallmessage,message);
            readcallbackfunc(complete_message);
        }
        //the message is uncomplete and should be instal into unordered_map 
        //if cache_number_of_all_message != cache_index  
        else{ 
            auto index_message = uncomplete_message.find(cache_number);
            if(index_message!=uncomplete_message.end()){
                LOG_FATAL("repeat number");
                return;
            }
            uncomplete_message[cache_number] = {cache_number_of_all_message,std::make_shared<ListBuffer>(countofallmessage,message)};
        }
    };

    
    //FIrst Time
    VariableSet();
    for(int count = 1;iter.Vaild() && countofmessage > count ;++count){
        number = mema::DecodeFixd32(GetHeaderNumber());
        if(cache_number == number){
            cache_index = mema::DecodeFixd32(GetHeaderIndex());
            ++countofallmessage;
            continue;
        }
        MessagePass();
        VariableSet();
    }
    MessagePass();
    return;
}


void FdChannel::SendOps()
{
    AddWriteFd();
}

void FdChannel::Send(std::string &str)
{
    SendOps();
    shared_ptr<WriteBuffer> writer = std::make_shared<WriteStringBuffer>(current_number,str);
    {
        MutexLockGuard lock_(unwritelist_lock);
        unwritelist.emplace_back(writer);
    }
}


void FdChannel::PrepareWriteBuffer(std::shared_ptr<ListBuffer>& message,int message_szie)
{

}
