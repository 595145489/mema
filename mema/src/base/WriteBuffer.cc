#include "src/base/WriteBuffer.h"
#include "src/base/Buffer.h"
#include "src/base/coding.h"

#include <math.h>
using namespace mema;

WriteBuffer::WriteBuffer(uint32_t number_):per_buffer_max_size(Buffer::GetDefaultMaxSize()),
                                           number(number_),
                                           current_send_index(1)
{

}

WriteBuffer::~WriteBuffer()
{

}

WriteBuffer* WriteBuffer::GetDefaultWriter(uint32_t number_,std::string& buffer)
{
    return new WriteStringBuffer(number_,buffer);
}


WriteStringBuffer::WriteStringBuffer(uint32_t number_,std::string& buffer):WriteBuffer(number_),
                                                                           buffer_(std::move(buffer))
                                                                           
{
    remain_size = buffer_.size();
    count_of_remain_message = ceil(remain_size/per_buffer_max_size);
}

WriteStringBuffer::~WriteStringBuffer()
{

}

void WriteStringBuffer::InsertoBuffer(Buffer* buffer)
{
    

}

