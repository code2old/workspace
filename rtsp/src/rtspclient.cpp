#include "log.h"
#include "rtspclient.h" 
#include "rtspurl.h"

#include <string>

using std::string;

void RtspClient::start(const string &url) {
    RtspUrl rtspUrl;
    rtspUrl.parse(url);
    LOGGER.setLogLevel("TRACE");
    LOG(FATAL, "url: %s, user: %s, passwd: %s, host: %s, port: %d", rtspUrl._url.data(), rtspUrl._user.data(), rtspUrl._passwd.data(), rtspUrl._host.data(), rtspUrl._port);
    LOG(ERROR, "url: %s, user: %s, passwd: %s, host: %s, port: %d", rtspUrl._url.data(), rtspUrl._user.data(), rtspUrl._passwd.data(), rtspUrl._host.data(), rtspUrl._port);
    LOG(WARN, "url: %s, user: %s, passwd: %s, host: %s, port: %d", rtspUrl._url.data(), rtspUrl._user.data(), rtspUrl._passwd.data(), rtspUrl._host.data(), rtspUrl._port);
    LOG(INFO, "url: %s, user: %s, passwd: %s, host: %s, port: %d", rtspUrl._url.data(), rtspUrl._user.data(), rtspUrl._passwd.data(), rtspUrl._host.data(), rtspUrl._port);
    LOG(DEBUG, "url: %s, user: %s, passwd: %s, host: %s, port: %d", rtspUrl._url.data(), rtspUrl._user.data(), rtspUrl._passwd.data(), rtspUrl._host.data(), rtspUrl._port);
    LOG(TRACE, "url: %s, user: %s, passwd: %s, host: %s, port: %d", rtspUrl._url.data(), rtspUrl._user.data(), rtspUrl._passwd.data(), rtspUrl._host.data(), rtspUrl._port);
}

