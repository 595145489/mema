#include "src/base/FileUtil.h"
#include "src/base/Buffer.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

using namespace mema;

FileUtil::FileUtil(const char* file_name):fp(::fopen(file_name,"wb+"))
{
    if(fp==nullptr){
        perror(file_name+' can not find');
    }
}

FileUtil::~FileUtil()
{
    this->Fclose();
}

void FileUtil::Fclose()
{
    ::fclose(fp);
    this->fp = nullptr;
}

void FileUtil::Fflush()
{
    ::fflush(fp);
}

void FileUtil::Seek(int offset,int orgin)
{
    ::fseek(fp,offset,orgin);
}

void FileUtil::FileAppend(const char* str)
{
    this->Seek(0,SEEK_END);
    ::fputs(str,this->fp);
    this->Fflush();
}

void FileUtil::FileBeginAppend(const char* str)
{
    this->Seek(0,SEEK_SET);
    ::fputs(str,this->fp);
    this->Fflush();
}

void FileUtil::operator<<(const char* str)
{
    this->FileAppend(str);
}

void FileUtil::FileAppend(Buffer& str)
{
    /* this->FileAppend(str.GetChar()); */
}

void FileUtil::FileBeginAppend(Buffer& str)
{
    /* this->FileBeginAppend(str.GetChar()); */
}

void FileUtil::operator<<(mema::Buffer& str)
{
    /* *this << str.GetChar(); */
}

