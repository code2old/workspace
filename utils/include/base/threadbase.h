#ifndef UTILS_BASE_THREAD_BASE_H_
#define UTILS_BASE_THREAD_BASE_H_

namespace utils {

class CThreadBase {
public:
    CThreadBase(){};
    /*析构函数*/
    virtual ~CThreadBase(){};
    /*起一个线程，开始运行*/
    virtual void start(void *func, void *arg) = 0;
    /*等待线程退出*/
    virtual void join() = 0;
};

}

#endif 