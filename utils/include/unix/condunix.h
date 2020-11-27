#ifndef UTILS_COND_UNIX_H_
#define UTILS_COND_UNIX_H_

#include <pthread.h>
#include "mutexunix.h"
#include "condbase.h"

namespace utils {

class CCondUnix : public CMutexUnix, public CCondBase {
public:
    CCondUnix();
    ~CCondUnix();
    int wait(int milliseconds = 0);
    int signal();
    int broadcast();
    int acquire();
    int release();
private:
    pthread_cond_t _cond;
};

}

#endif 