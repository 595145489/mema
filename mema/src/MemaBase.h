#pragma once
#include "src/FdChannel.h"

namespace mema{

class MemaBase
{
public:
    MemaBase() {}
    ~MemaBase() {}
    virtual void OnConnection(FdChannel* fd){};
    /* virtual void OnRead(FdChannel* fd,std::shared_ptr<ListBuffer> message){}; */
    virtual void OnRead(FdChannel* fd,std::string& message){};
    virtual void OnClose(FdChannel* fd){}; 

    /* virtual void OnWrite(FdChannel* fd){}; */
public:
};

}// end namespace

