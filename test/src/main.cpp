#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "test.h"
#include "log.h"

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        LOG(INFO, "usage: %s [option]", argv[0]);
        return -1;
    }
    if (strcmp(argv[1], "kfifo") == 0) {
        return test_kfifo(argc, argv);
    } else if (strcmp(argv[1], "cpuinfo") == 0) {
        return test_cpuinfo(argc, argv);
    } else if (strcmp(argv[1], "shell") == 0) {
        return test_shell(argc, argv);
    } else if (strcmp(argv[1], "log") == 0) {
        return test_log(argc, argv);
    } else if (strcmp(argv[1], "uuid") == 0) {
        return test_uuid(argc, argv);
    }
    return 0;
}