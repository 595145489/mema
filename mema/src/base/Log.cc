#include "src/base/Log.h"
#include "src/base/FileUtil.h"
#include "src/base/Buffer.h"

#include <assert.h>
#include <experimental/filesystem>

using namespace mema;
namespace fs = std::experimental::filesystem;

thread_local std::unique_ptr<Buffer> Log::log_buffer = std::make_unique<Buffer>(Buffer::GetDefaultMaxSize());
const char* LogLevelName[static_cast<int>(LogLevel::NUMBER_LEVEL)] = 
{
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN", 
    "ERROR",
    "FATAK"
};

const char* Log::GetLevelName(LogLevel message_level)
{
    return LogLevelName[static_cast<int>(message_level)];
}

Log::Log(const char* log_file_name,LogLevel level): local_level(level)
{
    /* fs::path log_path(log_file_name); */
    /* if(fs::exists(log_path)){ */

    /* } */
    log_file = std::make_unique<mema::FileUtil>((log_file_name)); 
    assert(log_file!=nullptr);
}

Log::~Log()
{

}

void Log::endoflocallog()
{
    
    *log_buffer << "\n";
    {
        MutexLockGuard lock(mutex_);
        *log_file << log_buffer->begin();
    }
    log_buffer->Clear();
    return ;
}

