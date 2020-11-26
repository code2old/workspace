#ifndef TOOLS_SHELL_SERVER_UNIX_H_
#define TOOLS_SHELL_SERVER_UNIX_H_

#include "shellbase.h"

namespace utils {

typedef struct ShellCmdContext {
    char cmdName[CMD_NAME_LEN];
    char cmdParm[CMD_PARM_LEN];
} SHELL_CMD_CONTEXT;

class ShellServerUnix : public ShellServerBase {
public:
    ShellServerUnix(){};
    ~ShellServerUnix(){}

    virtual void cmdLoop();
    virtual int regCmd(const char *cmdName, int(*callbackFunc)(void *, const char *, char *), void *callbackParam);
};

}

#endif 