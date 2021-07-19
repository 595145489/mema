# mema

## 简介
mema为一个服务端框架，其名字由来为个人最喜欢的动漫角色mema《未闻花名/我们仍未知道那天所看见的花的名字》。<br>
mema现今为v1.0.0测试版本,但是已经可以提供完备的服务端和客户端通信功能，于此同时，mema提供了各种基础类，包括日志,字符,字符集，互斥锁等功能。为了方便扩展，mema留出了大量接口类以供后期补充。<br>
就v1.0.0的完成程度仍然不高,仅完成了初期目标的百分之40左右,均已留下接口等待后期进行补充开发.

## 特点
* mema遵循谷歌编码标准 [ Google C++ 代码规范](https://google.github.io/styleguide/cppguide.html) 。
* mema广泛采用了 C++11/14的新的语法特性和标准,C++17由于测试过程中存在一定问题,暂时移除。
* mema提供了多种基础库包括日志,字符,字符集，互斥锁，编码解码等功能,在后期还会提供上层应用等接口，以供快速开发。
* mema提供了多种接口类，为协议扩充，分布式扩充等留下了接口，能快速扩充。

## 开始使用

### 安装
```shell
git clone https://github.com/595145489/mema.git
cd mema
mkdir build
cd build & cmake ..
make
make install
```
### 使用
这将形成一个空的应用,服务器接收信息后将不做任何处理。
```c++
#include "src/ThreadPool.h"
using namespace mema; 

DEFINE_string(SERVERADDR, "0.0.0.0", " if addr equal 0.0.0.0 the service will be server, else addr will be client ");
DEFINE_int32(PORT, 6002, "server listen port");

class Server:public MemaBase {};

int main()
{
    std::shared_ptr<ThreadPool> tp =  std::make_shared<ThreadPool>();
    MemaBase* server = new Server();
    tp->AddNewThread<ListenThread>(server,1);
    tp->start();
}
```

如果你想对服务器读取的信息进行处理，你可以这样做<br>
测试阶段只要string大小不超过51200字节均可顺利发送。上层已分装好了分片的设置。你只需要重载OnRead函数即可.
```c++
class Server:public MemaBase {
  virtual void OnRead(FdChannel* fd,std::string& message)override{//logic};
};
```
同样的，也可以设置连接时触发，和关闭时触发
```c++
 virtual void OnConnection(FdChannel* fd) override{//logic};
 virtual void OnClose(FdChannel* fd) override{//logic};
```
提供Send函数发送消息,现阶段只提供string类型和自定义的Buffer类型
```c++
std::string send_message("123");
fd->Send(send_message);
fd->SendNormal(send_message); //如果选择这个选项,则发送不带自定义协议的包,包的解析应该由应用层自行解决
```
如果是客户端的话，只需要修改为目标的IP和端口号即可
```c++
DEFINE_string(SERVERADDR, "X.X.X.X", " if addr equal 0.0.0.0 the service will be server, else addr will be client ");
DEFINE_int32(PORT, xxxx, "server listen port");
```
## 线程模型概述
mema v1.0.0测试版的服务端通信采用one-loop-per-thread线程模型,该模型拥有较好的支持高并发的能力(理论上)。<br><br>
现阶段允许对服务的线程数进行设置AddNewThread<ListenThread>(server,N)，N为线程数大小（理论上应该为核心数量，但是本框架不强制要求）。其理论上对i/o密集型友好，但是对计算密集型的任务并不友好。<br><br>
为此mema已留出扩展，将补充线程池，以提供计算密集型的支持，将来将为N个接受线程提供M个线程池以供非并发。于此同时，为了方便更大规模的接入，已留出了分布式的接口。<br><br>
## 内存池概述
mema v1.0.0测试版使用内存池.每个线程都将拥有51200字节的内存池.后期将采用两级内存池，此举是为了减少资源的浪费和考虑了一定的性能问题，一级内存池不变，由每个线程独自占有。二级内存池由所有线程共有，当内存不够时可以暂时"借"。

## 参考文献和代码
大量参考了muduo的代码 [ https://github.com/chenshuo/muduo ](https://github.com/chenshuo/muduo) <br>
大量参考了leveldb的代码 [ https://github.com/google/leveldb ](https://github.com/google/leveldb) <br>
部分参考了腾讯框架的风格[ https://github.com/Tencent/flare ](https://github.com/Tencent/flare) <br>
陈硕出版图书《Linux多线程服务端编程》 <br>
《unix环境高级编程》 <br>
  
## 个人想法&后期计划
本框架仍然是一个学习项目，不太具备线上生产的能力。前期在画框架图的时候画出了许多的功能,由于个人学业原因开发速度仍然比较慢.但是会慢慢更新.<br>
后期比较大的计划是完善线程池以提供计算密集型的支持和提供二级内存池。<br>
将协议逻辑移出FdChannel,以提供自定义的读协议<br>
现行的测试还远远不够，后期将引入google测试框架以实现测试的覆盖 [ https://github.com/google/googletest.git ]( https://github.com/google/googletest.git ) <br>

