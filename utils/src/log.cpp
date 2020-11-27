#include "log.h"

namespace utils {

CLogger CLogger::_logger;
const char *CLogger::_levelStr[] = {
    "FATAL",
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG",
    "TRACE"
};

const char *CLogger::_levelClr[] = {
    "\033[0;31m",
    "\033[0;35m",
    "\033[1;34m",
    "\033[0;32m",
    "\033[1;33m",
    "\033[1;37m"
};
#define NO_COLOR_LOG "\033[0m"

CLogger::CLogger() {
    _fd = fileno(stderr);
    _level = LOG_LEVEL_INFO;
    _filename = NULL;
    _check = 0;
    _maxFileSize = 0;
    _maxFileIndex = 0;
    _flag = false;
}

CLogger::~CLogger() {
    if (_filename != NULL) {
        free(_filename);
        _filename = NULL;
        close(_fd);
    }
}

void CLogger::setLogLevel(unsigned int level) {
    _level = level;
}

void CLogger::setLogLevel(const char *level) {
    if (NULL == level) {
        return;
    }
    int len = sizeof(_levelStr) / sizeof(char *);
    for (size_t i = 0; i < len; ++i) {
        if (strcasecmp(level, _levelStr[i]) == 0) {
            _level = (LOG_LEVEL)i;
            break;
        }
    }
}

void CLogger::setFileName(const char* filename, bool flag) {
    int fd = open(filename, O_CREAT | O_RDWR | O_APPEND | O_LARGEFILE, DEFAULT_FILE_MODE);
    if (fd < 0) {
        fprintf(stderr, "open log file %s failed. msg: %s(%d) ignored\n", filename, strerror(errno), errno);
        return;
    }
    if (_filename) {
        free(_filename);
        _filename = NULL;
    }
    _flag = flag;
    _filename = strdup(filename);
    if (!_flag) {
        /*重定向到新打开的文件*/
        dup2(fd, _fd);
        /*重定向到标准输出*/
        dup2(fd, 1);
        /*重定向到标准错误*/
        if (_fd != 2) {
            dup2(fd, 2);
        }
        close(fd);
    } else {
        if (_fd != 2) {
            dup2(fd, _fd);
            close(fd);
        }
        else {
            _fd = fd;
        }
    }
}

void CLogger::logMessage(int level, const char *filename, int line, const char *function, const char *fmt, ...) {
    if (level > _level) {
        return;
    }

    if(_check && _filename) {
        checkFile();
    }

    time_t t;
    time(&t);
    struct tm tm;
    localtime_r((const time_t *)&t, &tm);

    char data[LOG_DATA_LEN] = { 0 };
    char buffer[LOG_BUFFER_LEN] = { 0 };

    va_list args;
    va_start(args, fmt);
    vsnprintf(data, LOG_DATA_LEN, fmt, args);
    va_end(args);

    int size = 0;
    if (_filename) {
        size = snprintf(buffer, LOG_BUFFER_LEN, "[%04d-%02d-%02d %02d:%02d:%02d] %-5s %s (%s:%d) %s\n",
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec,
            _levelStr[level],
            function,
            filename,
            line,
            data);
    } else {
        size = snprintf(buffer, LOG_BUFFER_LEN, "%s[%04d-%02d-%02d %02d:%02d:%02d] %-5s %s (%s:%d) %s%s\n",
            _levelClr[level],
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min,
            tm.tm_sec,
            _levelStr[level],
            function,
            filename,
            line,
            data,
            NO_COLOR_LOG);
    }
    /*去掉多余的换行*/
    while (buffer[size - 2] == '\n') {
        --size;
    }

    buffer[size] = '\0';
    while (size > 0) {
        ssize_t success = ::write(_fd, buffer, size);
        if (success == -1) {
            fprintf(stderr, "write error: %s(%d)", strerror(errno), errno);
            break;
        }
        size -= success;
    }

    if (_maxFileSize) {
        utils::CGuard guard(&_fileSizeMutex);
        off_t offset = ::lseek(_fd, 0, SEEK_END);
        if (offset < 0) {
            /**/
            fprintf(stderr, "lseek failed: %s(%d)\n", strerror(errno), errno);
        } else if (static_cast<size_t>(offset) >= _maxFileSize) {
            rotateLog(NULL);
        }
    }
}

void CLogger::rotateLog(const char *filename, const char *fmt) {
    if (filename == NULL && _filename != NULL) {
        filename = _filename;
    }
    if (access(filename, R_OK) == 0) {
        char oldLogFile[LOG_OLD_FILE_NAME_LEN] = { 0 };
        time_t t;
        time(&t);
        struct tm tm;
        localtime_r((const time_t *)&t, &tm);

        if (fmt != NULL) {
            char tmptime[TMPE_TIME_STRING_LEN] = { 0 };
            strftime(tmptime, sizeof(tmptime), fmt, &tm);
            snprintf(oldLogFile, sizeof(oldLogFile), "%s.%s", filename, tmptime);
        } else {
            snprintf(oldLogFile, sizeof(oldLogFile), "%s.%04d%02d%02d%02d%02d%02d",
                filename,
                tm.tm_year + 1900,
                tm.tm_mon + 1,
                tm.tm_mday,
                tm.tm_hour,
                tm.tm_min,
                tm.tm_sec);
        }
        if (_maxFileIndex > 0) {
            utils::CGuard guard(&_fileIndexMutex);
            if (_fileList.size() >= _maxFileIndex) {
                std::string oldFile = _fileList.front();
                _fileList.pop_front();
                unlink(oldFile.c_str());
            }
            _fileList.push_back(oldLogFile);
        }
        rename(filename, oldLogFile);
    }
    int fd = open(filename, O_CREAT | O_RDWR | O_APPEND | O_LARGEFILE, DEFAULT_FILE_MODE);
    if (fd < 0) {
        return;
    }
    if (!_flag) {
        /*重定向到新打开的文件*/
        dup2(fd, _fd);
        /*重定向到标准输出*/
        dup2(fd, 1);
        /*重定向到标准错误*/
        if (_fd != 2) {
            dup2(fd, 2);
        }
        close(fd);
    } else {
        if (_fd != 2) {
            dup2(fd, _fd);
            close(fd);
        }
        else {
            _fd = fd;
        }
    }
}

void CLogger::checkFile() {
    struct stat stFile;
    struct stat stFd;
    fstat(_fd, &stFd);
    int err = stat(_filename, &stFile);
    if ((err == -1 && errno == ENOENT) || 
        (err == 0  && (stFile.st_dev != stFd.st_dev || stFile.st_ino != stFd.st_ino))) {
        int fd = open(_filename, O_CREAT | O_RDWR | O_APPEND | O_LARGEFILE, DEFAULT_FILE_MODE);
        if (fd < 0) {
            return;
        }
        if (!_flag) {
            /*重定向到新打开的文件*/
            dup2(fd, _fd);
            /*重定向到标准输出*/
            dup2(fd, 1);
            /*重定向到标准错误*/
            if (_fd != 2) {
                dup2(fd, 2);
            }
            close(fd);
        } else {
            if (_fd != 2) {
                dup2(fd, _fd);
                close(fd);
            }
            else {
                _fd = fd;
            }
        }
    }
}

void CLogger::setMaxFileSize( int64_t maxFileSize)
{   // 1GB
    if ( maxFileSize < 0x0 || maxFileSize > MAX_LOG_FILE_SIZE){
        maxFileSize = MAX_LOG_FILE_SIZE;//1GB 
    }
    _maxFileSize = maxFileSize;
}

void CLogger::setMaxFileIndex( int maxFileIndex )
{
    if ( maxFileIndex < 0x00 ) {
        maxFileIndex = MIN_LOG_FILE_INDEX;
    }
    if ( maxFileIndex > MAX_LOG_FILE_INDEX ) {//1024
        maxFileIndex = MAX_LOG_FILE_INDEX;//1024
    }
    _maxFileIndex = maxFileIndex;
}

void CLogger::setCheck(int v) {
    _check = v;
}
}