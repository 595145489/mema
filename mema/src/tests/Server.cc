#include "src/ThreadPool.h"
/* #include "src/thread/ListenThread.h" */
/* #include "src/thirdparty/gflags/include/gflags/gflags.h" */

#include <iostream>
using namespace mema; 

DEFINE_int32(PORT, 6002, "server listen port");
DEFINE_string(SERVERADDR, "0.0.0.0", " if addr equal 0.0.0.0 the service will be server, else addr will be client ");
/* DEFINE_string(SERVERADDR, "192.168.43.251", " if addr equal 0.0.0.0 the service will be server, else addr will be client "); */

class Server:public MemaBase {
public:
    /* virtual void OnConnection(FdChannel* fd) override{ */
    /*     std::string x(20*500,'q'); */
    /*     fd->Send(x); */
    /* } */
    virtual void OnRead(FdChannel* fd,std::string& message)override{
        std::cout << message << std::endl;
        std::string x("please close");
        fd->Send(x);
    }
};
int main()
{
    std::shared_ptr<ThreadPool> x(new ThreadPool());// = std::make_shared<ThreadPool>();
    MemaBase* xx = new Server();
    x->AddNewThread<ListenThread>(xx,1);
    x->start();
}
