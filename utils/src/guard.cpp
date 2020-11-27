#include "guard.h"
#include "mutex.h"

#include <iostream>

namespace utils {

CGuard::CGuard(CMutex *mutex): _mutex(NULL) {
    if (mutex) {
        _mutex = mutex;
        _mutex->lock();
    }
}

CGuard::~CGuard() {
    if (_mutex) {
        _mutex->unlock();
    }
}

}