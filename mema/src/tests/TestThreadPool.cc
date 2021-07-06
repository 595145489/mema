#include "src/ThreadPool.h"
#include "src/thread/ListenThread.h"
#include "src/MemaBase.h"

using namespace mema;

int main()
{
    std::shared_ptr<ThreadPool> x(new ThreadPool());// = std::make_shared<ThreadPool>();
    MemaBase* xx = new MemaBase();
    x->AddNewThread<ListenThread>(xx,1);
    x->start();
}
