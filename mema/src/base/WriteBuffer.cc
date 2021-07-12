#include "src/base/WriteBuffer.h"
#include "src/base/Buffer.h"
#include "src/base/coding.h"
#include "src/base/ListBuffer.h"

#include <math.h>
using namespace mema;

WriteBuffer::WriteBuffer(uint32_t number_):per_buffer_max_size(Buffer::GetDefaultMaxSize()),
                                           number(number_),
                                           current_send_index(1),
                                           send_position(0),
                                           header(new char[4]())
{
    EncodeFixed32(header.get(),number);
}

WriteBuffer::~WriteBuffer()
{

}

WriteBuffer* WriteBuffer::GetDefaultWriter(uint32_t number_,std::string& buffer)
{
    return new WriteStringBuffer(number_,buffer);
}

uint32_t WriteBuffer::InsertoBuffer(struct LocalWriteParm& parm,std::shared_ptr<ListBuffer> buffer)  
{
    auto iter = ListBuffer::Itertor(buffer);
    uint32_t list_count = 0;
    for(;iter.Vaild()&&list_count<parm.local_send_count&&parm.local_send_count;list_count++,iter.Next())
       InsertoBuffer(parm,iter.Get().get()); 
    return list_count;
}


WriteStringBuffer::WriteStringBuffer(uint32_t number_,std::string& buffer):WriteBuffer(number_),
                                                                           buffer_(std::move(buffer))
                                                                           
{
    remain_size = buffer_.size();
    // remain_size + 4 is the first buffer need to add total count of message
    // per_buffer_max_size mean  that each messgae should add 8 bytes head(number and index) 
    count_of_remain_message = ceil( static_cast<float>(remain_size+4) / ( per_buffer_max_size - header_size));

}

WriteStringBuffer::~WriteStringBuffer()
{

}

void WriteStringBuffer::InsertoBuffer(struct LocalWriteParm& parm,Buffer* buffer)
{
    uint32_t total_header_size = header_size;
    buffer->append(header.get(),4);
    char index_c[4];

    EncodeFixed32(index_c,parm.local_current_send_index);
    buffer->append(index_c,4);

    if(parm.local_current_send_index == 1){
        char total_size_c[4];
        EncodeFixed32(total_size_c,parm.local_count_of_remain_message);
        buffer->append(total_size_c,4);
        total_header_size += 4;
    }

    uint32_t copy_size = parm.local_remain_size>per_buffer_max_size?per_buffer_max_size:parm.local_remain_size;
    copy_size = copy_size>per_buffer_max_size-total_header_size?copy_size-total_header_size:copy_size;
    buffer->append(buffer_,parm.local_send_position,copy_size);
    parm.local_remain_size-=copy_size;
    parm.local_send_position+=copy_size;
    --parm.local_send_count;
    parm.local_current_send_index++;
}

