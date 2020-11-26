#ifndef UTILS_SINGLETON_H_
#define UTILS_SINGLETON_H_

#include <iostream>
#include "guard.h"

namespace utils {

template <typename T>
class Singleton {
public:
    static inline T* getInstance() {
        if (0 == instance) {
            CGuard guard(&mutex);
            if (0 == instance) {
                instance = new T;
            }
        }
        return instance;
    }

    static inline void release() {
        bfree = true;
        CGuard guard(&mutex);
        if (instance != 0) {
            delete instance;
            instance = 0;
        }
    }

protected:
    Singleton() {}
    virtual ~Singleton() {
        if (!bfree) {
            bfree = true;
            CGuard guard(&mutex);
            if (instance != 0) {
                delete instance;
                instance = 0;
            }
        }
    }

private:
    Singleton(const Singleton&) {}
    Singleton& operator=(const Singleton&){}

private:
    static T *instance;
    static CMutex mutex;
    static bool bfree;
};

template <typename T>
T *Singleton<T>::instance = NULL;

template <typename T>
CMutex Singleton<T>::mutex;

template <typename T>
bool Singleton<T>::bfree = false;

}


#endif 