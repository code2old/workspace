#include "stl_test.h"

int lambdas_test(int argc, char *argv[]) {
    [] {
        std::cout << "Hello lambda" << endl;
    }();
    auto l = [] {
        cout << "test lambda" << endl;
    };
    l();

    int id = 0;
    auto f = [id]() mutable {
        std::cout << "id: " << id << endl;
        ++id;
    };
    id = 42;
    f();
    f();
    f();
    cout << id << endl;
    return 0;
}