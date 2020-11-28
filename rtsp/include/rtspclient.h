#ifndef MEDIA_RTSP_CLIENT_H_
#define MEDIA_RTSP_CLIENT_H_

#include <string>

class RtspClient {
public:
    void start(const std::string &url);
};

#endif 