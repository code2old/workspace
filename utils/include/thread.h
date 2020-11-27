#ifndef UTILS_THREAD_H_
#define UTILS_THREAD_H_

namespace utils {

class Runnable;
class CThreadBase;
class CThread {
public:
    /*构造函数*/
    CThread();
    /*析构函数*/
    ~CThread();
    /*起一个线程，开始运行*/
    void start(Runnable *r, void *arg);
    /*等待线程退出*/
    void join();
    /*获取Runnable对象*/
    Runnable *getRunnable();
    /*获取回调参数*/
    void *getArgs();
    /*获取线程的进程ID*/
    int getpid();
    /*获取线程ID*/
    int gettid();
    /*线程的回调函数*/
    static void *hook(void *arg);
private:
    void *_args;
    utils::Runnable *_runnable;
    utils::CThreadBase *m_thread;
};

}

#endif 