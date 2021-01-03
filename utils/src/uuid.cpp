#include <iostream>
#include "uuid.h"
#include "log.h"

#ifdef _WIN32 
#include <windows.h>
#include <time.h>
#define EPOCHFILETIME 11644473600000000Ui64
#elif __linux__
#include <sys/time.h>
#define EPOCHFILETIME 11644473600000000ULL
#else
# error "Unknown Compiler"
#endif

namespace utils {

static uint64_t get_time() {
#ifdef _WIN32
    FILETIME filetime;
    uint64_t time = 0;
    GetSystemTimeAsFileTime(&filetime);

    time |= filetime.dwHighDateTime;
    time <<= 32;
    time |= filetime.dwLowDateTime;

    time /= 10;
    time -= EPOCHFILETIME;
    return time / 1000;
#elif __linux__ 
    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t time = tv.tv_usec;
    time /= 1000;
    time += (tv.tv_sec * 1000);
    return time;
#else
# error "Unknown Compiler"
#endif 
}

uint64_t uuid::_epoch    = 0;
uint64_t uuid::_time     = 0;
int32_t  uuid::_machine  = 0;
std::atomic<int32_t> uuid::_sequence(0);

uuid::uuid() {

}

uuid::~uuid() {
}

void uuid::setEpoch(uint64_t epoch) {
    _epoch = epoch;
}

void uuid::setMachine(int32_t machine) {
    _machine = machine;
}

int64_t uuid::generate() {
    int64_t value = 0;
    uint64_t time = get_time() - _epoch;
    /*保留后41位时间*/
    value = time << 22;
    /*中间10位是机器ID*/
    value |= (_machine & 0x03FF) << 12;
    /*最后12位是sequence id*/
    value |= (++_sequence) & 0x0FFF;
    return value;
}

}
