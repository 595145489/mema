#include "src/base/ListBuffer.h"
#include "src/base/Buffer.h"


using namespace mema;

ListBuffer::ListBuffer(int buffer_size,uint32_t per_buffer_size): total_size(buffer_size),
                                                                  list_buffer(0)
{
    for(int count = 0 ;count < buffer_size; ++count){
        list_buffer.emplace_back(new Buffer(per_buffer_size));
    }
}

ListBuffer::ListBuffer(int buffer_size,std::shared_ptr<ListBuffer> list_):total_size(0)
{
    EmplaceBack(list_,buffer_size);
}

ListBuffer::~ListBuffer()
{ 

}

std::shared_ptr<ListBuffer> ListBuffer::GetNewBuffer(int get_size)
{
    std::shared_ptr<ListBuffer> cache_buffer = std::make_shared<ListBuffer>(get_size,shared_from_this());
    return std::move(cache_buffer);
}

void ListBuffer::EmplaceBack(std::shared_ptr<ListBuffer> cache_buffer,int emplace_size)
{
    Itertor iter(cache_buffer); 
    for(int count = 0;iter.Vaild() && emplace_size > count ;++count){
        iter.RemoveFrom([&](std::unique_ptr<Buffer> c_ptr)->void{
            list_buffer.emplace_back(std::move(c_ptr));
        });
        ++total_size;
    }
}

void ListBuffer::EmplaceBackAndClear(std::shared_ptr<ListBuffer> cache_buffer,int emplace_size)
{
    Itertor iter(cache_buffer); 
    for(int count = 0;iter.Vaild() && emplace_size > count ;++count){
        iter.RemoveFrom([&](std::unique_ptr<Buffer> c_ptr)->void{
            c_ptr->Clear();
            list_buffer.emplace_back(std::move(c_ptr));
        });
        ++total_size;
    }
}


ListBuffer::Itertor::Itertor(std::shared_ptr<ListBuffer>& list_):list_(list_),
                                                              Iter(list_->list_buffer.begin()) { }

ListBuffer::Itertor::Itertor(Itertor& iter_):list_(iter_.list_),
                                              Iter(iter_.Iter) { }

void ListBuffer::Itertor::operator=(Itertor& iter_)
{
    Iter = iter_.Iter;
}

bool ListBuffer::Itertor::Vaild() const
{
    return list_->total_size>0; 
}

void ListBuffer::Itertor::Next() 
{
    ++Iter;
}

void ListBuffer::Itertor::SeekToFirst() 
{
    Iter = list_->list_buffer.begin(); 
}

void ListBuffer::Itertor::SeekTolAST()
{
    Iter = list_->list_buffer.end(); 
}

void ListBuffer::Itertor::RemoveFrom(ListBuffer::HandleElementFunc handlefunc)
{
    handlefunc(std::move(*Iter));
    list_->list_buffer.erase(Iter++);
    --(list_->total_size);
}

std::unique_ptr<Buffer>& ListBuffer::Itertor::Get() const
{
    return *Iter; 
}
ListBuffer::ListIter& ListBuffer::Itertor::GetIter() 
{
    return Iter;
}

