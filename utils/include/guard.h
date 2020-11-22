#ifndef UTILS_GUARD_H_
#define UTILS_GUARD_H_

namespace utils {

class CMutex;
class CGuard {
public:
    CGuard(CMutex *mutex);
    ~CGuard();
private:
    CMutex *_mutex;
};


}


#endif 