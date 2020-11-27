#ifndef UTILS_SHELL_HANDLER_H_
#define UTILS_SHELL_HANDLER_H_

#include <queue>
#include <string>

#include "cond.h"
#include "thread.h"
#include "runnable.h"

namespace utils {

#define SEND_BUF_LEN (512*1024)

typedef struct TaskItem {
    int fd;
    std::string cmdParm;
    void *callbackParm;
    int (*callbackFunc)(void *, const char *recvBuf, char *sendBuf);
} TASK_ITEM;

class ShellCmdHandler : public utils::Runnable {
public:
    ShellCmdHandler();
    ~ShellCmdHandler();

    int init();
    void run(utils::CThread *thread, void *arg);
    void submission(TASK_ITEM &item);
    void stop();

private:
    utils::CCond          _cond;
    utils::CThread        _thread;
    std::queue<TASK_ITEM> _task;
    bool _stop;
};

}

#endif 