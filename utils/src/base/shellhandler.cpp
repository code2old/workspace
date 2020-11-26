#include "log.h"
#include "common.h"
#include "shellhandler.h"

namespace utils {

ShellCmdHandler::ShellCmdHandler() {
    _stop = false;
}

ShellCmdHandler::~ShellCmdHandler() {
}

int ShellCmdHandler::init() {
    _thread.start(this, NULL);
    return EXIT_SUCCESS;
}

void ShellCmdHandler::stop() {
    _cond.lock();
    _stop = true;
    _cond.broadcast();
    _cond.unlock();
}

void ShellCmdHandler::submission(TASK_ITEM &item) {
    if (_stop) {
        return;
    }
    _cond.lock();
    _task.push(item);
    _cond.unlock();
    _cond.signal();
}

void ShellCmdHandler::run(utils::CThread *thread, void *arg) {
    while (!_stop) {
        _cond.lock();
        while (!_stop && _task.empty() ) {
            _cond.wait();
        }
        if (_stop) {
            _cond.unlock();
            break;
        }
        TaskItem item = _task.front();
        _task.pop();
        _cond.unlock(); 

        char sendBuf[SEND_BUF_LEN] = { 0 };
        if (item.callbackFunc != NULL) {
            item.callbackFunc(item.callbackParm, item.cmdParm.data(), sendBuf);
        }
        if (strlen(sendBuf) > 0) {
            int nwrite = write(item.fd, sendBuf, strlen(sendBuf));
            if (nwrite < 0) {
                LOG(ERROR, "fd[%d] write data failed: [%d]%s", item.fd, errno, strerror(errno));
            }
        }
        close(item.fd);
    }
}

}