#include "memory_test.h"

void noMoreMemory() {
    cerr << "out of memory";
    abort();
}

int new_handler_test(int argc, char *argv[]) {
    set_new_handler(noMoreMemory);
    int *p = nullptr;

    p = new int[0x7FFFFFFF];
    assert(p);
    p = new int[0x7FFFFFFF];
    assert(p);
    p = new int[0x7FFFFFFF];
    assert(p);
    p = new int[0x7FFFFFFF];
    assert(p);
    return 0;
}