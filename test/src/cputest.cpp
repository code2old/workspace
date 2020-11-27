#include "test.h"
#include "cpu.h"
#include "log.h"

int test_cpuinfo(int argc, char *argv[]) {
    for (;;) {
        LOG(INFO, "cpu rate: %0.2f", utils::CPU::getInstance()->getUseRate(1));
    }
    return 0;
    
}

