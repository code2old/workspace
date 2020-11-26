#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>

#include "log.h"
#include "common.h"
#include "fileutil.h"
#include "shellunix.h"

namespace utils {

#define LISTEN_QUEUE_LEN 10
#define SHELL_CMD_PATH   "/usr/local/sbin/"
#define SHELL_TOOLS_PATH "/usr/local/sbin/shellTools"
#define SHELL_SUN_PATH   "/usr/local/etc/cmd.socket"

static int serv_listen(const char *name) {
    /*create a UNIX domain stream socket*/
    int fd = 0;
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        LOG(ERROR, "create socket failed: [%d]%s", errno, strerror(errno));
        return EXIT_FAILED;
    }
    /*in case it already exists*/
    unlink(name);

    /*fill in socket address structure*/
    int len = 0;
    struct sockaddr_un un;
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strncpy(un.sun_path, name, sizeof(un.sun_path));
    len = offsetof(struct sockaddr_un, sun_path) + strlen(name);

    /*bind the name to the discriptor*/
    if (bind(fd, (struct sockaddr *)&un, len) < 0) {
        LOG(ERROR, "bind fd[%d] failed: [%d]%s", fd, errno, strerror(errno));
        close(fd);
        return EXIT_FAILED;
    }
    /*change sun_path's permission*/
    if (chmod(un.sun_path, 0777) < 0) {
        LOG(ERROR, "chmod %s permission failed [%d]%s", un.sun_path, errno, strerror(errno));
        close(fd);
        return EXIT_FAILED;
    }

    if (listen(fd, LISTEN_QUEUE_LEN) < 0) {
        LOG(ERROR, "listen fd[%d] failed [%d]%s", fd, errno, strerror(errno));
        close(fd);
        return EXIT_FAILED;
    }
    return fd;
}

static int serv_accept(int listenfd, uid_t *uidptr) {
    struct sockaddr_un un;
    int len = sizeof(un);
    int clifd = 0;
    if ((clifd = accept(listenfd, (struct sockaddr *)&un, (socklen_t *)&len)) < 0) {
        LOG(ERROR, "accept fd[%d] failed: [%d]%s", listenfd, errno, strerror(errno));
        return EXIT_FAILED;
    }
    /*obtain the client's uid from its calling address*/
    len -= offsetof(struct sockaddr_un, sun_path);  /*len of pathname*/
    un.sun_path[len] = 0;
    struct stat st;
    if (stat(un.sun_path, &st) < 0) {
        LOG(ERROR, "stat %s failed: [%d]%s", un.sun_path, errno, strerror(errno));
        close(clifd);
        return EXIT_FAILED;
    }

    if ((st.st_mode & (S_IRWXG | S_IRWXO)) || (st.st_mode & S_IRWXU) != S_IRWXU) {
        LOG(ERROR, "%s stat is error: 0x%x", un.sun_path, st.st_mode);
        close(clifd);
        return EXIT_FAILED;
    }
    if (uidptr != NULL) {
        *uidptr = st.st_uid;    /*return uid of caller*/
    }
    unlink(un.sun_path);
    return clifd;
}

void ShellServerUnix::cmdLoop() {
    if (!_handler.init()) {
        LOG(ERROR, "_handle start failed");
        return;
    }
    int listenfd = serv_listen(SHELL_SUN_PATH);
    if (listenfd < 0) {
        LOG(ERROR, "serv_listen failed");
        return;
    }
    TASK_ITEM taskItem = { 0 };
    SHELL_CMD_CONTEXT cmdContext = { 0 };
    std::map<std::string, SHELL_CMD_UNIT>::iterator it;
    for (;;) {
        uid_t uid = 0;
        int fd = serv_accept(listenfd, &uid);
        if (fd < 0) {
            LOG(ERROR, "accept fd[%d] failed: [%d]%s", listenfd, errno, strerror(errno));
            continue;
        }
        LOG(INFO, "accept a new socket %d, uid is %d", fd, (int)uid);
        memset(&cmdContext, 0, sizeof(SHELL_CMD_CONTEXT));
        int nread = recv(fd, &cmdContext, sizeof(cmdContext), 0);
        if (nread <= 0) {
            LOG(ERROR, "fd[%d] recv data len: %d, faild: [%d]%s", fd, nread, errno, strerror(errno));
            close(fd);
            continue;
        }
        it = m_shell.find(std::string(cmdContext.cmdName));
        if (it == m_shell.end()) {
            LOG(ERROR, "fd[%d] recv cmd %s faild", fd, cmdContext.cmdName);
            close(fd);
            continue;
        }
        SHELL_CMD_UNIT cmdUnit = it->second;
        taskItem.fd = fd;
        taskItem.cmdParm = std::string(cmdContext.cmdParm);
        taskItem.callbackFunc = cmdUnit.callbackFunc;
        taskItem.callbackParm = cmdUnit.callbackParm;
        _handler.submission(taskItem);
    }
    return;
}

int ShellServerUnix::regCmd(const char *cmdName, int(*callbackFunc)(void *, const char *, char *), void *callbackParam) {
    if (regShellCmd(cmdName, callbackFunc, callbackParam) < 0) {
        LOG(ERROR, "regShellCmd failed");
        return EXIT_FAILED;
    }
    char shellName[128] = { 0 };
    if (isFileExist(SHELL_TOOLS_PATH)) {
        std::string shellName(SHELL_CMD_PATH);
        shellName += std::string(cmdName);
        symlink(SHELL_TOOLS_PATH, shellName.data());
    } else {
        LOG(ERROR, "%s not exist!!!", SHELL_TOOLS_PATH);
    }
    return EXIT_SUCCESS;
}

}

