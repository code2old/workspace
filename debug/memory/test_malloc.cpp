#include "memory_test.h"

int malloc_test(int argc, char *argv[]) {
    char *p = (char *)malloc(8);
    cout << p << endl;
    return 0;
}