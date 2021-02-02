#include "stl_test.h"

class Zoo {
public:
    Zoo(int i1, int i2): d1(i1), d2(i2) {}
    Zoo(const Zoo&) = delete;
    Zoo(Zoo &&) = default;
    Zoo &operator=(const Zoo&) = default;
    Zoo &operator=(const Zoo&&) = delete;
    virtual ~Zoo(){}
private:
    int d1, d2;
};

int default_test(int argc, char *argv[]) {
    return 0;
}