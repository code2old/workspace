

#include "threadunix.h"
#include "runnable.h"

namespace utils {

CThreadUnix::CThreadUnix() {
    _tid = 0;
}

CThreadUnix::~CThreadUnix() {
}

void CThreadUnix::start(void *func, void *arg) {
    int ret = pthread_create(&_tid, NULL, (void* (*)(void*))func, arg);
    if (ret < 0) {
    }
    return;
}

void CThreadUnix::join() {
    if(_tid) {
        pthread_join(_tid, NULL);
        _tid = 0;
    }
}

}