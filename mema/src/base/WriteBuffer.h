#pragma once
#include "src/base/noncopyable.h"
#include "src/base/MutexLock.h"

#include <string>
namespace mema{
class Buffer;
class ListBuffer;

class WriteBuffer:noncopyable
{
public:
    WriteBuffer(uint32_t number_);
    virtual ~WriteBuffer();
    uint32_t GetNumber(){return number;};
    uint32_t GetRemainSize(){return remain_size;};
    uint32_t GetRemainCount(){ return count_of_remain_message; };
    void DeductionCount(uint32_t deduct_count){ count_of_remain_message-=deduct_count; }
    bool IsRemainCount(){ return GetRemainCount()<=0; };

    static WriteBuffer* GetDefaultWriter(uint32_t number_,std::string& buffer);
    virtual void InsertoBuffer(Buffer* buffer) ; 
    virtual void InsertoBuffer(ListBuffer* buffer,int list_size) ; 
public:
    size_t per_buffer_max_size;
    MutexLock lock_;
    uint32_t number;
    uint32_t current_send_index;
    uint32_t remain_size;
    uint32_t count_of_remain_message;
};

class WriteStringBuffer : public WriteBuffer
{
public:
    WriteStringBuffer(uint32_t number_,std::string& buffer);
    ~WriteStringBuffer();
    virtual void InsertoBuffer(Buffer* buffer) override ; 
private:
    std::string buffer_;
};


}// end namespace


