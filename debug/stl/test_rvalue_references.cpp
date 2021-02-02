#include "stl_test.h"

class MoveTest {
public:
    MoveTest(int d) {
        data = d;
        memcpy(value, "hello, world", sizeof(value));
    }
public:
    int data;
    char value[128];
};

static void move_test(vector<MoveTest>& test) {
    MoveTest m1(1);
    cout << m1.data << ": " << m1.value << endl;
    MoveTest m2(m1);
    cout << m2.data << ": " << m2.value << endl;
    MoveTest m3(move(m1));
    cout << m3.data << ": " << m3.value << endl;
    cout << m1.data << ": " << m1.value << endl;
    test.push_back(move(m1));
}

class A {
    int * p;

public:
    A(int value) :
        p(new int(value))
    {
        cout << "new pointer:   " << (void *)p << endl;
    }

    //A &operator=(const A& rhs) {
    //    if (p) {
    //        delete p;
    //    }
    //    memcpy(p, rhs.p, sizeof(p));
    //}

    ~A() {
        std::cout << "delete pointer:" << (void *)p << std::endl;
        //查看析够函数删除了哪个指针
        // delete p;
    }

};

int rvalue_references_test(int argc, char *argv[]) {
    //string s1("hello");
    //string s2("world");
    //s1 + s2 = s2;
    //string() = "World";
    //cout << s1 << " : " << s2 << endl;
    vector<MoveTest> t;
    move_test(t);
    cout << &t[0].data << ": "<< t[0].data << ": " << t[0].value << endl;

    A a(1);
    A b(2);

    std::swap(a, b);

    return 0;
}