#include "memory_test.h"

class MemTest {};

int cookie_test(int argc, char *argv[]) {
    const int N = 60;
    cout << sizeof(MemTest) << endl;
    vector<MemTest> vt;
    for (int i = 0; i < N; ++i) {
        vt.push_back(MemTest());
    }
    return 0;
}