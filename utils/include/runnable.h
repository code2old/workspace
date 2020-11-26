#ifndef UTILS_RUNNABLE_H_
#define UTILS_RUNNABLE_H_

namespace utils {

class CThread;
/*CRunnable是一个抽象类，它拥有一个纯虚方法，主要用于CThread类*/
class Runnable {
public:
    virtual ~Runnable();
    virtual void run(CThread *thread, void *argv) = 0;
};

}



#endif 