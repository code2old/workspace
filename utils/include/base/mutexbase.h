#ifndef UTILS_BASE_MUTEX_BASE_H_
#define UTILS_BASE_MUTEX_BASE_H_

namespace utils {

class CMutexBase {
public:
    CMutexBase(){}
    /*析构函数*/
    virtual ~CMutexBase(){};
    /*上锁*/
    virtual int lock() = 0;
    /**/
    virtual int trylock() = 0;
    /**/
    virtual int unlock() = 0; 
};

}

#endif 