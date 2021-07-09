#pragma once
//To do 
//we must to create a new string buffer
#include "src/base/noncopyable.h"
#include "src/thirdparty/gflags/include/gflags/gflags.h"

//just debug
#include <iostream>

#include <cstring>
#include <string>
#include <vector>
#include <endian.h>


DECLARE_int32(PROTOCAL_SIZE);

namespace mema{

class Buffer:noncopyable
{
typedef Buffer self; 
typedef std::vector<char> CharType;
public:
    //the last char must be \0
    // this construction function is cu
    /* Buffer():freesize(max_size-1), */
    /*          vchar(max_size), */
    /*          size(0), */
    /*          current_position(begin()) */
    /* { */
    /*     std::cout << "creat buffer" << std::endl; */
    /*     vchar[size] = '\0'; */
    /* } */
    Buffer(int size):buffer_max_size(size),
                     freesize(size), 
                     vchar(size),
                     size(0),
                     current_position(begin())
    {
        std::cout << "creat buffer" << std::endl;
        vchar[size] = '\0';
    }
    ~Buffer() {
        Clear();
    }

    static uint32_t GetDefaultMaxSize(){
        return FLAGS_PROTOCAL_SIZE; 
    }

    std::string GetString(){
        std::string str(begin(),size);
        return std::move(str);
    }
    size_t FreeSize(){
        return freesize;
    }
    size_t Size(){
        return size;
    }
    void Seek(int size){
        current_position+=size;
    }
    char* IterPosition(){
        return current_position;
    }

    char* begin(){
        return &*vchar.begin();
    }
    char* beginWrite(){
        return begin()+size;
    }
    void append(const char* s,size_t size_){
        std::copy(s,s+size_,beginWrite());
        AddVChar(size_);
    }
    void append(char* s,size_t size_){
        std::copy(s,s+size_,beginWrite());
        AddVChar(size_);
    }
    void append(void* s,size_t size_){
        append(static_cast<const char*>(s),size_);
    }
    void append(const char* s){
        size_t size_ = std::strlen(s);
        append(s,size_);
    }
    self& operator<<(const char *s){
        append(s);
        return *this;
    }
    self& operator<<(char s){
        append(static_cast<char*>(&s),1);
        return *this;
    }
    self& operator<<(std::string s){
        append(s.c_str(),s.size());
        return *this;
    }

    self& operator<<(int s){
        int size_ = snprintf(beginWrite(),freesize,"%d",s);
        AddVChar(size_);
        return *this;
    }
    self& operator<<(unsigned int s){
        int size_ = snprintf(beginWrite(),freesize,"%u",s);
        AddVChar(size_);
        return *this;
    }
    self& operator<<(double s){
        int size_ = snprintf(beginWrite(),freesize,"%.3lf",s);
        AddVChar(size_);
        return *this;
    }
    self& operator<<(float s){
        int size_ = snprintf(beginWrite(),freesize,"%.3f",s);
        AddVChar(size_);
        return *this;
    }
    self& operator<<(long s){
        int size_ = snprintf(beginWrite(),freesize,"%ld",s);
        AddVChar(size_);
        return *this;
    }
    self& operator<<(long long s){
        int size_ = snprintf(beginWrite(),freesize,"%lld",s);
        AddVChar(size_);
        return *this;
    }
    self& operator<<(long unsigned int s){
        int size_ = snprintf(beginWrite(),freesize,"%lu",s);
        AddVChar(size_);
        return *this;
    }
    self& operator<<(bool s){
        const char tmp = s?'1':'0';
        append(&tmp,1);
        return *this;
    }
    void Clear(){
        size = 0;
        freesize = buffer_max_size-1; 
        SetEnd();
        current_position = begin();
    }
    size_t GetMaxSize(){
        return buffer_max_size-1;
    }
    bool SetSize(size_t insert_size){
        if(insert_size>freesize){
            return false;
        }
        freesize-=insert_size;
        size += insert_size;
        return true;
    }
    

private:
    void AddVChar(size_t count){
        size+=count;
        freesize-=count;
        SetEnd();
    }
    void SubVChar(size_t count){
        size-=count;
        freesize+=count;
        SetEnd();
    }
    void SetEnd(){
        vchar[size] = '\0';
    }

private:
    /* static const size_t max_size; */
    uint32_t buffer_max_size;
    size_t freesize;
    CharType vchar;
    size_t size;
    char* current_position;
    
};
}// end namespace

