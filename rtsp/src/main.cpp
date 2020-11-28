#include "rtspclient.h"

int main(int argc, char *argv[]) {
    RtspClient client;
    client.start("rtsp://admin:hik12345@10.12.117.218:554/ch1/main/av_stream?linkmode=tcp?smversion=4");
    return 0;
}