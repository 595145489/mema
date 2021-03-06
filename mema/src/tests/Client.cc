#include "src/ThreadPool.h"
#include "src/thread/ListenThread.h"
#include "src/MemaBase.h"
#include "src/thirdparty/gflags/include/gflags/gflags.h"

#include <iostream>
using namespace mema; 

DEFINE_int32(PORT, 6002, "server listen port");
/* DEFINE_string(SERVERADDR, "0.0.0.0", " if addr equal 0.0.0.0 the service will be server, else addr will be client "); */
/* DEFINE_string(SERVERADDR, "127.0.0.1", " if addr equal 0.0.0.0 the service will be server, else addr will be client "); */
DEFINE_string(SERVERADDR, "192.168.43.251", " if addr equal 0.0.0.0 the service will be server, else addr will be client ");

class Client:public MemaBase {
public:
    virtual void OnConnection(FdChannel* fd) override{
        std::string x(500,'q');
        x+="xxxaaa";
        fd->SendNormal(x);
    }
    virtual void OnRead(FdChannel* fd,std::string& message)override{
        std::cout << message << std::endl;
        fd->OnClose();
    }
};


int main()
{
    std::shared_ptr<ThreadPool> x(new ThreadPool());// = std::make_shared<ThreadPool>();
    MemaBase* xx = new Client();
    x->AddNewThread<ListenThread>(xx,1);
    x->start();
}
