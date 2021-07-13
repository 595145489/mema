#pragma once
#include "src/FdChannel.h"

namespace mema{

class MemaBase
{
public:
    MemaBase() {}
    ~MemaBase() {}
    void OnConnection(FdChannel* fd){
        std::string x(500*10,'q');
        /* std::string x; */
        fd->Send(x);
    }

private:

public:
};

}// end namespace

