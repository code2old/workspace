#ifndef TOOLS_SHELL_H_
#define TOOLS_SHELL_H_

#include "singleton.h"

namespace utils {

class ShellServerBase;
class ShellServer : public utils::Singleton<ShellServer> {
public:
    ShellServer();
    ~ShellServer();
    int init();
    int regCmd(const char *cmdName, int(*callbackFunc)(void *, const char *, char *), void *callbackParam);
private:
    ShellServerBase *m_shell;
};

}

#endif 