#pragma once
#include "src/base/noncopyable.h"

#include <deque>
#include <memory>
#include <functional>

namespace mema{

class FdChannel;

class ChannelList : public noncopyable
{
typedef std::function<void(FdChannel*)> HandleFunction;
public:
    ChannelList(); 
    ~ChannelList(); 

    void PushBack(FdChannel* val);
    FdChannel* PopFront();
    int GetSize();
    void ForEachThenRemove(HandleFunction func);
private:
    int list_size;
    std::deque<FdChannel*> list_;
};

}// end namespace

