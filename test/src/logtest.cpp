#include "test.h"
#include "log.h"

int test_log(int argc, char *argv[]) {
    LOG(FATAL, "log test");
    LOG(ERROR, "log test");
    LOG(WARN, "log test");
    LOG(INFO, "log test");
    LOG(DEBUG, "log test");
    LOG(TRACE, "log test");
    return 0;
}