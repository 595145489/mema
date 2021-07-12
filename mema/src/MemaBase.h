#pragma once
#include "src/FdChannel.h"

namespace mema{

class MemaBase
{
public:
    MemaBase() {}
    ~MemaBase() {}
    void OnConnection(FdChannel* fd){
        std::string x("123");
        fd->Send(x);
    }

private:

public:
};

}// end namespace

