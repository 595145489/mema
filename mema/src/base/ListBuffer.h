#pragma once
#include "src/base/noncopyable.h"
#include "src/base/Buffer.h"

#include <deque>
#include <memory>
#include <functional>

namespace mema{

class Buffer;

// thread unsafe
class ListBuffer :public  std::enable_shared_from_this<ListBuffer> 
{
typedef std::deque<std::unique_ptr<Buffer>> ListType;
typedef std::deque<std::unique_ptr<Buffer>>::iterator ListIter;
typedef std::function<void(std::unique_ptr<Buffer>)> HandleElementFunc;
/* Itertor cIter) */
public:
    ListBuffer(int buffer_size,uint32_t per_buffer_size = Buffer::GetDefaultMaxSize());
    ListBuffer(int buffer_size,std::shared_ptr<ListBuffer> list_);
    ~ListBuffer();

    std::shared_ptr<ListBuffer> GetNewBuffer(int get_size);
    void EmplaceBack(std::shared_ptr<ListBuffer> cache_buffer,int emplace_size);
    void EmplaceBackAndClear(std::shared_ptr<ListBuffer> cache_buffer,int emplace_size);

    int GetTotalSize(){ return total_size; }
    /* // todo */ 
    class Itertor{
    public:
        Itertor(std::shared_ptr<ListBuffer>& list_);
        Itertor(Itertor& iter_);
        void operator=(Itertor& iter_);
        bool Vaild() const;
        void Next() ;
        void SeekToFirst();
        void SeekTolAST(); 
        void RemoveFrom(HandleElementFunc handlefunc);
        std::unique_ptr<Buffer>& Get() const;
        ListIter& GetIter();
    private:
        std::shared_ptr<ListBuffer>& list_;
        ListIter Iter;
    };
private:
    int total_size;
    ListType list_buffer;
};

}// end namespace


