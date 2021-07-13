#pragma once
#include "src/FdChannel.h"

namespace mema{

class MemaBase
{
public:
    MemaBase() {}
    ~MemaBase() {}
    virtual void OnConnection(FdChannel* fd){
        /* std::string x(500*4,'q'); */
        /* std::string x; */
        /* fd->Send(x); */
    }

private:

public:
};

}// end namespace

