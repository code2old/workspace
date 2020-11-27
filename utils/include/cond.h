#ifndef UTILS_COND_H_
#define UTILS_COND_H_

namespace utils {

class CMutex;
class CCondBase;
class CCond {
public:
    CCond();
    ~CCond();
    int wait(int milliseconds = 0);
    int signal();
    int broadcast();
    int lock();
    int unlock();
private:
    utils::CCondBase *m_cond;
};

}

#endif