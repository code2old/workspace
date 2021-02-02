#include "stl_test.h"

class MyString {
};

template <typename T, template<class > class Container>
void test_movable() {
    Container<T> c;
    for (long i = 0; i < 10; ++i) {
        c.insert(c.end(), T());
    }
    // output_static_data(T());
    Container<T> c1(c);
    Container<T> c2(std::move(c));
    c1.swap(c2);
}

template <typename T, template <class> class Container>
class XCIs {
public:
    XCIs() {
        for (int i = 0; i < 10; ++i) {
            c.insert(c.end(), T());
        }
        Container<T> c1(c);
        Container<T> c2(std::move(c));
        c1.swap(c2);
    }
private:
    Container<T> c;
};

template <typename T>
using Vec = vector<T, std::allocator<T>>;

int alias_template_test(int argc, char *argv[]) {
    XCIs<MyString, Vec> c1;
    test_movable<MyString, Vec>();
    return 0;
}