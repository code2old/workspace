#include <sys/time.h>
#include <sys/types.h>

#include "condunix.h"

namespace utils {

CCondUnix::CCondUnix() {
    const int ret = pthread_cond_init(&_cond, NULL);
}

CCondUnix::~CCondUnix() {
    pthread_cond_destroy(&_cond);
}

int CCondUnix::wait(int milliseconds) {
    int ret = 0;
    if (0 == milliseconds) {
        return pthread_cond_wait(&_cond, &_mutex);
    } else {
        struct timeval curtime;
        struct timespec abstime;
        gettimeofday(&curtime, NULL);
        int64_t us = (static_cast<int64_t>(curtime.tv_sec) * static_cast<int64_t>(1000000) + 
                      static_cast<int64_t>(curtime.tv_usec) * static_cast<int64_t>(milliseconds) * static_cast<int64_t>(1000));
        abstime.tv_sec  = static_cast<int>(us / static_cast<int64_t> (1000000));
        abstime.tv_nsec = static_cast<int>(us % static_cast<int64_t> (1000000) * 1000);
        return pthread_cond_timedwait(&_cond, &_mutex, &abstime);
    }
    return 0;
}

int CCondUnix::signal() {
    return pthread_cond_signal(&_cond);
}

int CCondUnix::broadcast() {
    return pthread_cond_broadcast(&_cond);
}

int CCondUnix::acquire() {
    return lock();
}

int CCondUnix::release() {
    return unlock();
}

}