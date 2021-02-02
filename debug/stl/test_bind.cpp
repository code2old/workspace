#include <random>
#include <iostream>
#include <memory>
#include <functional>

#include "stl_test.h"

using namespace std;

void f(int n1, int n2, int n3, const int &n4, int n5) {
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << endl;
}

int g(int n1) {
    return n1;
}

struct Foo {
    void print_sum(int n1, int n2) {
        cout << n1 + n2 << endl;
    }
    int data = 10;
};

int bind_test(int argc, char *argv[]) {
    using namespace std::placeholders;
    int n = 7;
    auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);
    n = 10;
    f1(1, 2, 1001);

    auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
    f2(10, 11, 12);

    std::default_random_engine e;
    std::uniform_int_distribution<> d(0, 10);
    auto rnd = std::bind(d, e);
    for (int n = 0; n < 10; ++n) {
        std::cout << rnd() << ' ';
    }
    cout << endl;

    Foo foo;
    auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
    f3(5);

    auto f4 = std::bind(&Foo::data, _1);
    std::cout << f4(foo) << std::endl;

    std::cout << f4(std::make_shared<Foo>(foo)) << '\n'
        << f4(std::make_unique<Foo>(foo)) << '\n';
    return 0;
}