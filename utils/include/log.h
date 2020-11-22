#ifndef UTILS_LOG_H_
#define UTILS_LOG_H_

#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <deque>
#include <string>
#include <pthread.h>
#include <sys/time.h>

#include "mutex.h"
#include "guard.h"
#include "string.h"

#define MAX_LOG_FILE_SIZE      0x40000000
#define MIN_LOG_FILE_INDEX     0x0f
#define MAX_LOG_FILE_INDEX     0xff
#define DEFAULT_FILE_MODE      0640
#define TMPE_TIME_STRING_LEN   256
#define LOG_OLD_FILE_NAME_LEN  256
#define LOG_DATA_LEN          (4*1024)
#define LOG_BUFFER_LEN        (6*1024)

typedef enum LogLevel {
    LOG_LEVEL_FATAL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARN  = 2,
    LOG_LEVEL_INFO  = 3,
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5
} LOG_LEVEL;

/*不优雅*/
#define LOG_FILE                   (strrchr(__FILE__,'/')+1)
#define LOG_LEVEL(level)           LOG_LEVEL_##level, LOG_FILE, __LINE__, __FUNCTION__
#define LOGGER                     utils::CLogger::_logger
#define LOG_PRINT(level, ...)      LOGGER.logMessage(LOG_LEVEL(level), __VA_ARGS__)
#define LOG_BASE(level, ...)       (LOG_PRINT(level, __VA_ARGS__))
#define LOG(level, _fmt_, args...) (LOG_BASE(level, "[%ld] " _fmt_, pthread_self(), ##args))

namespace utils {

/*简单日志系统*/
class CLogger {
public:
    CLogger();
    ~CLogger();
    /** 
     * @brief 将日志内容写入文件
     * 
     * @param level 日志的级别
     * @param file  日志内容所在的文件
     * @param line  日志内容所在的文件的行号
     * @param function 写入日志内容的函数名称
     * @param fmt
     * @param ...
     */
    void rotateLog(const char *filename, const char *fmt = NULL);
    void logMessage(int level, const char *filename, int line, const char *function, const char *fmt, ...);
    void setLogLevel(unsigned int level);
    void setLogLevel(const char *level);
    void setFileName(const char *filename, bool flag = false);
    void checkFile();
    void setCheck(int v);
    void setMaxFileSize(int64_t maxFileSize = MAX_LOG_FILE_SIZE);
    void setMaxFileIndex(int maxFileIndex = MAX_LOG_FILE_INDEX);
    static inline struct timeval get_cur_tv() {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return tv;
    };

public:
    static CLogger _logger;
    int _level;

private:
    int _fd;
    char *_filename;
    int _check;
    size_t _maxFileIndex;
    int64_t _maxFileSize;
    bool _flag;
private:
    static const char *_levelStr[];
    static const char *_levelClr[];
    std::deque<std::string> _fileList;
    utils::CMutex _fileSizeMutex;
    CMutex _fileIndexMutex;

};

}

#endif 