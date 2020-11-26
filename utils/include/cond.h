#ifndef UTILS_COND_H_
#define UTILS_COND_H_

namespace utils {

class CCondBase;
class CCond {
public:
    CCond();
    ~CCond();
    int wait(int milliseconds = 0);
    int signal();
    int broadcast();
private:
    utils::CCondBase *m_cond;
};

}

#endif