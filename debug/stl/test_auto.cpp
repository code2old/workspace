#include "stl_test.h"

static void  print(std::initializer_list<int> vals) {
    for (auto p = vals.begin(); p != vals.end(); ++p) {
        cout << *p << endl;
    }
}

int auto_test(int argc, char *argv[]) {

    //int x1(5.3);
    //int x2 = 5.3;
    //int x3{ 5.0 };
    //int x4 = { 5.0 };

    print({ 10,3,5,123,51 });

    return 0;
}