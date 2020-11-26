#ifndef UTILS_COND_BASE_H_
#define UTILS_COND_BASE_H_

namespace utils {

class CCondBase {
public:
    CCondBase();
    virtual ~CCondBase();
    virtual int wait(int milliseconds = 0) = 0;
    virtual int signal() = 0;
    virtual int broadcast() = 0;
};

}

#endif