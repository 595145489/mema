#include "src/ChannelList.h"
#include "src/base/Log.h"

using namespace mema;

ChannelList::ChannelList():list_size(0)
{
    list_.clear();
}

ChannelList::~ChannelList() 
{
    list_.clear();
}

void ChannelList::PushBack(FdChannel* val)
{
    list_.emplace_back(val);
    ++list_size;
}

FdChannel* ChannelList::PopFront()
{
    if(list_size<=0) {
        LOG_ERROR("FdChannel has been empty");
        return nullptr;
    }
    FdChannel* tmp = list_.front();
    list_.pop_front();
    --list_size;
    return tmp;
}

int ChannelList::GetSize()
{
    return list_size;
}

void ChannelList::ForEachThenRemove(HandleFunction func)
{
    while(list_size>0){
        func(PopFront());
    }
}

