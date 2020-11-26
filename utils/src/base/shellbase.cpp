#include "log.h"
#include "common.h"
#include "shellbase.h"

#include <iostream>
#include <utility>

namespace utils {

ShellServerBase::ShellServerBase() {
}

ShellServerBase::~ShellServerBase() {
}

int ShellServerBase::start() {
    _thread.start(this, NULL);
    return 0;
}

void ShellServerBase::run(utils::CThread *thread, void *arg) {
    cmdLoop();
}

int ShellServerBase::regShellCmd(const char *cmdName, int(*callbackFunc)(void *, const char *, char *), void *callbackParm){
    if (NULL == cmdName || NULL == callbackFunc) {
        LOG(ERROR, "cmdName or callbackFunc is NULL");
        return EXIT_FAILED;
    }
    if (!isCmdValid(cmdName)) {
        LOG(ERROR, "the cmd(%s) not valid", cmdName);
        return EXIT_FAILED;
    }
    SHELL_CMD_UNIT cmdUnit = { 0 };
    cmdUnit.cmdName = std::string(cmdName);
    cmdUnit.callbackFunc = callbackFunc;
    cmdUnit.callbackParm = callbackParm;
    _mutex.lock();
    m_shell[std::string(cmdUnit.cmdName)] = cmdUnit; /*std::move(cmdUnit);*/
    _mutex.unlock();
    return EXIT_SUCCESS;
}

bool ShellServerBase::isCmdValid(const char *cmdName) {
    CGuard guard(&_mutex);
    std::map<std::string, SHELL_CMD_UNIT>::iterator it;
    it = m_shell.find(std::string(cmdName));
    if (it == m_shell.end()) {
        return true;
    }
    return false;    
}

}