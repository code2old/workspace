#ifndef UTILS_MUTEX_H_
#define UTILS_MUTEX_H_

namespace utils {

class CMutexBase;
class CMutex {
public:
    /*构造函数*/
    CMutex();
    /*析构函数*/
    virtual ~CMutex();
    /*上锁*/
    int lock();
    /*尝试上锁*/
    int trylock();
    /*解锁*/
    int unlock();
protected:
    utils::CMutexBase *m_mutex;
};

}

#endif 