#ifndef UTILS_UNIX_MUTEX_H_
#define UTILS_UNIX_MUTEX_H_

#include <pthread.h>
#include "mutexbase.h"

namespace utils {

class CMutexUnix : public utils::CMutexBase {
public:
    /*构造函数*/
    CMutexUnix();
    /*析构函数*/
    ~CMutexUnix();
    /*上锁*/
    int lock();
    /**/
    int trylock();
    /**/
    int unlock(); 

protected:
    pthread_mutex_t _mutex;

};

}

#endif 