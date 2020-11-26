#include "shell.h"
#ifdef _WIN32
    #include "shellwin32.h"
#elif __linux__
    #include "shellunix.h"
#else
    #error "Unknown compiler"
#endif 

namespace utils {

ShellServer::ShellServer() {
#ifdef _WIN32
    m_shell = new utils::ShellServerWin32;
#elif __linux__
    m_shell = new utils::ShellServerUnix;
#else
    #error "Unknown compiler"
#endif 
}

ShellServer::~ShellServer() {
    if (m_shell != NULL) {
        delete m_shell;
        m_shell = NULL;
    }
}

int ShellServer::init() {
    return m_shell->start();
}

int ShellServer::regCmd(const char *cmdName, int(*callbackFunc)(void *, const char *, char *), void *callbackParam) {
    return m_shell->regCmd(cmdName, callbackFunc, callbackParam);
}

}
