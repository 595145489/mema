#pragma once
#include "src/base/noncopyable.h"
#include "src/base/MutexLock.h"

#include <string>
#include <memory>
namespace mema{
class Buffer;
class ListBuffer;

// create the struct to suppose multi thread
struct LocalWriteParm{
    uint32_t local_current_send_index;
    uint32_t local_count_of_remain_message;// all of the buffer size divide per_buffer_size
    uint32_t local_remain_size; // all of the buffer remain
    uint32_t local_send_position;
    uint32_t local_send_count;
};

class WriteBuffer:noncopyable
{
public:
    WriteBuffer(uint32_t number_);
    virtual ~WriteBuffer();

    void GetlocalParm(struct LocalWriteParm& parm,uint32_t message_size);
    uint32_t GetNumber(){return number;};
    uint32_t GetRemainSize(){return remain_size;};
    uint32_t GetRemainCount(){ return count_of_remain_message; };

    void DeductionCount(uint32_t deduct_count){ count_of_remain_message-=deduct_count; }
    void DeductionRemainSie(uint32_t deduct_size){ remain_size-=deduct_size; }
    bool HaveRemainCount(){ return GetRemainCount()>0; };
    void IncreaseIndex(uint32_t increase_size){ current_send_index+=increase_size; }
    void IncreaseSendPosition(uint32_t increase_size){ send_position+=increase_size; }
    

    static WriteBuffer* GetDefaultWriter(uint32_t number_,std::string& buffer);
    virtual void InsertoBuffer(struct LocalWriteParm& parm,Buffer* buffer) = 0; 
    uint32_t InsertoBuffer(struct LocalWriteParm& parm,std::shared_ptr<ListBuffer> buffer) ; 
protected:
    const uint32_t header_size = 8;

    size_t per_buffer_max_size;
    MutexLock lock_;
    uint32_t number;
    uint32_t current_send_index;
    uint32_t remain_size; // all of the buffer remain
    uint32_t count_of_remain_message;// all of the buffer size divide per_buffer_size
    uint32_t send_position;
    std::unique_ptr<char[]> header;
};

class WriteStringBuffer : public WriteBuffer
{
public:
    WriteStringBuffer(uint32_t number_,std::string& buffer);
    ~WriteStringBuffer();
    virtual void InsertoBuffer(struct LocalWriteParm& parm,Buffer* buffer) override ; 
    /* virtual void InsertoBuffer(ListBuffer* buffer,int list_size) override; */ 
private:
    std::string buffer_;
};


}// end namespace


