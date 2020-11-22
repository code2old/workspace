#include <stdio.h>
#include "mutex.h"
#ifdef _WIN32
#elif __linux__
#include "mutex_unix.h"
#else
# error  "Unknown Compiler"

#endif

namespace utils {


/*构造函数*/
CMutex::CMutex() {
#ifdef _WIN32
#elif __linux__
    m_mutex = new utils::CMutexUnix;
#else
# error  "Unknown Compiler"

#endif
}
/*析构函数*/
CMutex::~CMutex() {
    if (m_mutex != NULL) {
        delete m_mutex;
        m_mutex = NULL;
    }
}
/*上锁*/
int CMutex::lock() {
    return m_mutex->lock();
}
/*尝试上锁*/
int CMutex::trylock() {
    return m_mutex->trylock();
}
/*解锁*/
int CMutex::unlock() {
    return m_mutex->unlock();
}



}