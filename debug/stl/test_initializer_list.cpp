#include "stl_test.h"

static void  print(std::initializer_list<int> vals) {
    for (auto p = vals.begin(); p != vals.end(); ++p) {
        cout << *p << endl;
    }
}

class P {
public:
    P(int a, int b) {
        cout << "P(int, int), a=" << a << ", b=" << b << endl;
    }
    //P(initializer_list<int> initlist) {
    //    for (auto p = initlist.begin(); p != initlist.end(); ++p) {
    //        cout << *p << ' ';
    //    }
    //    cout << endl;
    //}
    P &operator=(const P& other) {
        cout << "Copy ctor" << endl;
        return *this;
    }
};

int initializer_list_test(int argc, char *argv[]) {
    P p(77, 5);
    P q{ 77, 7 };
    // P r{ 77, 55, 23 };
    P ss = { 77, 5 };
    return 0;
}