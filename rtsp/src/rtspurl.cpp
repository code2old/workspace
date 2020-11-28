#include "rtspurl.h"
#include "stringutil.h"
#include "log.h"

#include <string>
#include <iostream>
#include <sstream>
#include <string.h>

using std::string;

static string findField(const char *buf, const char *start, const char *end, int bufsize) {
    if (bufsize <= 0) {
        bufsize = strlen(buf);
    }
    int len = 0;
    const char *msg_start = buf;
    const char *msg_end   = buf + bufsize;
    
    if (start != NULL) {
        len = strlen(start);
        msg_start = strstr(buf, start);
    }
    if (msg_start == NULL) {
        return "";
    }
    msg_start += len;
    if (end != NULL) {
        msg_end = strstr(msg_start, end);
        if (msg_end == NULL) {
            return "";
        }
    }
    return string(msg_start, msg_end);
}

int RtspUrl::parse(const string &url) {
    string schema = findField(url.data(), nullptr, "://", 0);
    bool isSSL = strcasecmp(schema.data(), "rtsps") == 0;
    /*����://��/֮����ַ�����������ȡ�û�������*/
    string middleUrl = findField(url.data(), "://", "/", 0);
    if (middleUrl.empty()) {
        middleUrl = findField(url.data(), "://", nullptr, 0);
    }
    size_t pos = middleUrl.rfind('@');
    if (pos == string::npos) {
        /*��û���û���������*/
        return setup(isSSL, url, "", "");
    }

    /*�����û�������*/
    string userPasswd = middleUrl.substr(0, pos);
    string suffix     = url.substr(schema.size() + strlen("://") + pos + strlen("/"));
    string newUrl     = string("rtsp://");
    newUrl           += suffix;
    if (userPasswd.find(":") == string::npos) {
        return setup(isSSL, newUrl, userPasswd, "");
    }

    string user   = findField(userPasswd.data(), nullptr, ":", 0);
    string passwd = findField(userPasswd.data(), ":", nullptr, 0);
    return setup(isSSL, newUrl, user, passwd);
}

int RtspUrl::setup(bool isSSL, const string &url, const string &user, const string &passwd) {
    string ip = findField(url.data(), "://", "/", 0);
    if (ip.empty()) {
        ip = utils::StringUtil::split(findField(url.data(), "://", nullptr, 0), "?")[0];
    }
    int port = atoi(findField(ip.data(), ":", nullptr, 0).data());
    if (port <= 0 || port > UINT16_MAX) {
        /*rtspĬ�϶˿�554*/
        port = isSSL ? 322 : 554;
    } else {
        /*����������*/
        ip = findField(ip.data(), nullptr, ":", 0);
    }
    if (ip.empty()) {
        return -1;
    }
    _url = std::move(url);
    _user = std::move(user);
    _passwd = std::move(passwd);
    _host = std::move(ip);
    _port = port;
    _bSSL = isSSL;
    return 0;
}
