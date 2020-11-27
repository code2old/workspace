#ifndef UTILS_UNIX_THREAD_H_
#define UTILS_UNIX_THREAD_H_

#include <pthread.h>
#include "threadbase.h"

namespace utils {

class CThreadUnix : public utils::CThreadBase {
public:
    CThreadUnix();
    /*析构函数*/
    virtual ~CThreadUnix();
    /*起一个线程，开始运行*/
    void start(void *func, void *arg);
    /*等待线程退出*/
    void join();
private:
    pthread_t _tid;
};

}

#endif 