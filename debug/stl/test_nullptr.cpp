#include "stl_test.h"

static void foo(int value) {
    cout << value << endl;
}

static void foo(void *value) {
    if (value == NULL) {
        cout << "NULL" << endl;
    }
    else {
        cout << "Not NULL" << endl;
    }
}

int nullptr_test(int argc, char *argv[]) {
    int *t1 = NULL;
    int *t2 = nullptr;
    int t3 = 0;
    foo(t1);
    foo(t2);
    foo(t3);
    cout << __cplusplus << endl;
    return 0;
}