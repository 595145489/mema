#pragma once
#include "src/writerbatch/WriteBuffer.h"

namespace mema{

class WriteStringBufferNormal :public WriteBuffer
{
public:
    WriteStringBufferNormal(uint32_t number_,std::string& buffer);
    ~WriteStringBufferNormal();
    virtual void InsertoBuffer(struct LocalWriteParm& parm,Buffer* buffer) override ; 
    virtual void  GetlocalParm(struct LocalWriteParm& parm,uint32_t message_size) override;
private:
    std::string buffer_;
};

}// end namespace

