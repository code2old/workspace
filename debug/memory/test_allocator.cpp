#include "allocator_test.h"
#include "memory_test.h"

class MemGoo {
    DECLARE_POOL_ALLOC();
public:
    long l;
    string str;
};

IMPLEMENT_POOL_ALLOC(MemGoo);

int allocator_test(int argc, char *argv[]) {
    size_t const N = 100;
    MemGoo *p[N] = { 0 };
    for (int i = 0; i < N; ++i) {
        p[i] = new MemGoo;
    }

    for (int i = 0; i < N; ++i) {
        delete p[i];
    }
    cout << sizeof(MemGoo) << endl;
    return 0;
}