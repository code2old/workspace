#ifndef TOOLS_SHELL_BASE_H_
#define TOOLS_SHELL_BASE_H_

#include <map>
#include <string>
#include "mutex.h"
#include "thread.h"
#include "runnable.h"
#include "shellhandler.h"

namespace utils {

#define CMD_NAME_LEN 32
#define CMD_PARM_LEN 1024

typedef struct ShellCmdUnit {
    std::string cmdName;
    int (*callbackFunc)(void *, const char *recvBuf, char *sendBuf);
    void *callbackParm;
} SHELL_CMD_UNIT;

class ShellServerBase : public utils::Runnable{
public:
    ShellServerBase();
    virtual ~ShellServerBase();
    virtual int start();
    virtual void run(utils::CThread *thread, void *arg);

    virtual void cmdLoop() = 0;
    virtual int regCmd(const char *cmdName, int(*callbackFunc)(void *, const char *, char *), void *callbackParam) = 0;

protected:
    int regShellCmd(const char *cmdName, int(*callbackFunc)(void *, const char *, char *), void *callbackParam);

private:
    bool isCmdValid(const char *cmdName);

protected:
    utils::CMutex  _mutex;
    utils::CThread _thread;
    utils::ShellCmdHandler _handler;
    std::map<std::string, SHELL_CMD_UNIT> m_shell;
};

}

#endif 