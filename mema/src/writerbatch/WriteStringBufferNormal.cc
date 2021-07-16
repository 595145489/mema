#include "src/writerbatch/WriteStringBufferNormal.h"
#include "src/base/ListBuffer.h"

#include "math.h"

using namespace mema;

WriteStringBufferNormal::WriteStringBufferNormal(uint32_t number_,std::string& buffer):WriteBuffer(number_),
                                                                                       buffer_(std::move(buffer))
{

    remain_size = buffer_.size();
    // remain_size + 4 is the first buffer need to add total count of message
    // per_buffer_max_size mean  that each messgae should add 8 bytes head(number and index) 
    count_of_remain_message = ceil( static_cast<float>(remain_size) /  per_buffer_max_size );
}


WriteStringBufferNormal::~WriteStringBufferNormal()
{

}

void WriteStringBufferNormal::InsertoBuffer(struct LocalWriteParm& parm,Buffer* buffer)
{
    uint32_t copy_size = parm.local_remain_size>per_buffer_max_size?per_buffer_max_size:parm.local_remain_size;
    buffer->append(buffer_,parm.local_send_position,copy_size);
    parm.local_remain_size-=copy_size;
    parm.local_send_position+=copy_size;
    --parm.local_send_count;
    parm.local_current_send_index++;
}

void  WriteStringBufferNormal::GetlocalParm(struct LocalWriteParm& parm,uint32_t message_size){
    parm.local_current_send_index = current_send_index;
    parm.local_count_of_remain_message = count_of_remain_message;
    parm.local_send_position = send_position;
    if(count_of_remain_message<message_size){
        parm.local_send_count = count_of_remain_message;
        parm.local_remain_size = remain_size;
    }
    else{
        parm.local_send_count = message_size;
        parm.local_remain_size = message_size * per_buffer_max_size ;
    }
    CutVariantFromParm(parm);
}
