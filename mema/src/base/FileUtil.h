#pragma once
#include "src/base/noncopyable.h"

#include<stdio.h>

namespace mema{

class Buffer;

class FileUtil:noncopyable
{
public:
    FileUtil(const char* file_name); 
    ~FileUtil();

    void Fflush();
    void FileAppend(const char* str);
    void FileBeginAppend(const char* str);
    void FileAppend(Buffer& str);
    void FileBeginAppend(Buffer& str);
    void Readfromfile(char *str);
    void Seek(int offset,int orgin);
    void Fclose();
    void operator<<(Buffer& str);
    void operator<<(const char* str);

private:
    FILE* fp;

};

}// end namespace

