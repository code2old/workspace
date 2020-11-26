#include <stdio.h>
#include "thread.h"
#include "runnable.h"
#ifdef _WIN32
#elif __linux__
#include "threadunix.h"
#else
# error "Unknown Compiler"
#endif

namespace utils {

/*构造函数*/
CThread::CThread() {
    m_thread = NULL;
#ifdef _WIN32
#elif __linux__
    m_thread = new utils::CThreadUnix;
#else
#error "Unknown Compiler"
#endif 
}

/*析构函数*/
CThread::~CThread() {
    if (m_thread != NULL) {
        delete m_thread;
        m_thread = NULL;
    }
}

/*起一个线程，开始运行*/
void CThread::start(Runnable *r, void *arg) {
    _runnable = r;
    _args = arg;
    return m_thread->start((void *)CThread::hook, arg);
}

/*等待线程退出*/
void CThread::join() {
    return m_thread->join();
}
/*获取Runnable对象*/
Runnable *CThread::getRunnable() {
    return _runnable;
}
/*获取回调参数*/
void *CThread::getArgs() {
    return _args;
}
/*获取线程的进程ID*/
int CThread::getpid() {
    return 0;
}

/*获取线程ID*/
int CThread::gettid() {
    return 0;
}

/*线程的回调函数*/
void *CThread::hook(void *arg) {
    CThread *thread = (CThread *)arg;
    if (thread->getRunnable()) {
        thread->getRunnable()->run(thread, thread->getArgs());
    }
    return (void *)NULL;
}

}