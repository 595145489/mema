#pragma once
#include "src/base/noncopyable.h"
#include "src/base/Buffer.h"
#include "src/base/MutexLock.h"
#include "src/base/ThreadBase.h"

#include <memory>

// if the class has bug, we must to include iostream to debug it 
// but we must not include iostream in the release verson. because it is too big.
#ifndef SYS_LOG_FILE
#define SYS_LOG_FILE "SysLogfile"
#endif
#ifndef DEFAULT_LOG_FORMAT
#define LOG_FORMAT ThreadBase::GetThreadId() << __FILE__ << ":" << __LINE__ 
#define LOG_END Log::DefaultSystemLog().endoflocallog()
#define LOG_TRACE(messages) Log::DefaultSystemLog() << Log::GetLevelName(mema::LogLevel::TRACE) << LOG_FORMAT << messages; LOG_END
#define LOG_DEBUG(messages) Log::DefaultSystemLog() << Log::GetLevelName(mema::LogLevel::DEBUG) << LOG_FORMAT << messages; LOG_END
#define LOG_INFO(messages) Log::DefaultSystemLog() << Log::GetLevelName(mema::LogLevel::INFO) << LOG_FORMAT << messages; LOG_END
#define LOG_WARN(messages) Log::DefaultSystemLog() << Log::GetLevelName(mema::LogLevel::WARN) << LOG_FORMAT << messages; LOG_END
#define LOG_ERROR(messages) Log::DefaultSystemLog() << Log::GetLevelName(mema::LogLevel::ERROR) << LOG_FORMAT << messages; LOG_END
#define LOG_FATAL(messages) Log::DefaultSystemLog() << Log::GetLevelName(mema::LogLevel::FATAL) << LOG_FORMAT << messages; LOG_END
#endif

//to do  make it more safe and effictive
namespace mema{

class Buffer;
class FileUtil;

enum class LogLevel{
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5,
    NUMBER_LEVEL = 6
};

class Log:noncopyable
{
typedef Log self;
private:
    template<typename str_type>
    void LogFormat(Buffer& buffer,str_type str)
    {
        buffer << str;
        buffer << " ";
    }
public:
    Log(const char* log_file_name,LogLevel level = LogLevel::DEBUG);
    ~Log();

    static Log& DefaultSystemLog(){
        static self system_log(SYS_LOG_FILE); 
        return system_log;
    };

    template<typename str_type>
    self& operator<<(str_type str)
    {
        LogFormat(*log_buffer,str);
        return *this;
    };
    static const char* GetLevelName(LogLevel message_level);

    void endoflocallog();
    
private:
    //std::unique_ptr<Buffer> log_buffer;
    std::unique_ptr<FileUtil> log_file;
    LogLevel local_level;
    mutable MutexLock mutex_;
    static thread_local std::unique_ptr<Buffer> log_buffer;
};

}// end namespace

