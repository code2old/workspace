#ifndef RTSP_RTSP_URL_H_
#define RTSP_RTSP_URL_H_

#include <string>

class RtspUrl {
public:
    RtspUrl() = default;
    ~RtspUrl() = default;
    int parse(const std::string &url);
public:
    std::string _url;
    std::string _user;
    std::string _passwd;
    std::string _host;
    uint16_t    _port;
    bool        _bSSL;
private:
    int setup(bool, const std::string&, const std::string&, const std::string&);
};


#endif 