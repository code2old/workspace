#include "mutex_unix.h"

namespace utils {

CMutexUnix::CMutexUnix() {
    const int ret = pthread_mutex_init(&_mutex, NULL);
}

CMutexUnix::~CMutexUnix() {
    pthread_mutex_destroy(&_mutex);
}

int CMutexUnix::lock() {
    return pthread_mutex_lock(&_mutex);
}

int CMutexUnix::trylock() {
    return pthread_mutex_trylock(&_mutex);
}

int CMutexUnix::unlock() {
    return pthread_mutex_unlock(&_mutex);
} 

}