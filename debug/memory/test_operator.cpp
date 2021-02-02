#include "memory_test.h"

static void *myalloc(size_t size) {
    return malloc(size);
}

static void myfree(void *ptr) {
    return free(ptr);
}

class Bad {
public:

};

class MemFoo {
public:
    MemFoo() : _id(0) {
        cout << "default ctor.this=" << this << " id=" << _id << endl;
    }
    MemFoo(int i) :_id(i) {
        cout << "ctor.this=" << this << " id=" << _id << endl;
        // throw Bad();
    } 
    virtual ~MemFoo() {
        cout << "dtor.this=" << this << " id=" << _id << endl;
    }
public:
    void *operator new(size_t size) {
        cout << "global new("<< size << ")" << endl;
        return myalloc(size);
    }
    void operator delete(void *ptr, size_t size) {
        cout << "global delete(" << ptr << ", " << size << ")" << endl;
        return myfree(ptr);
    }
    void *operator new[](size_t size) {
        cout << "global new[" << size << "]" << endl;
        return myalloc(size);
    }
    void operator delete[](void *ptr, size_t size) {
        cout << "global delete[" << ptr << ", " << size << "]" << endl;
        return myfree(ptr);
    }

    void *operator new(size_t size, void *start) {
        cout << "operator new(" << size << ", " << start << ")" << endl;
        return start;
    }
    void *operator new(size_t size, long extra) {
        cout << "operator new(" << size << ", " << extra << ")" << endl;
        return myalloc(size + extra);
    }
    void *operator new(size_t size, long extra, char init) {
        cout << "operator new(" << size << ", " << extra << ", " << init << ")" << endl;
        return myalloc(size + extra);
    }

    void operator delete(void *ptr, void *start) {
        cout << "operator delete(void *, void *)" << endl;
        // return myfree(ptr);
    }

    void operator delete(void *ptr, long extra) {
        cout << "operator delete(void *, long)" << endl;
        return myfree(ptr);
    }
    void operator delete(void *ptr, long extra, char init) {
        cout << "operator delete(void *, long, init)" << endl;
        return myfree(ptr);
    }
public:
    int _id;
    long _data;
    string _str;
};

void test_operator_new() {
    cout << "=======================================" << endl;
    MemFoo start;
    MemFoo *p1 = new MemFoo;
    MemFoo *p2 = new(&start) MemFoo;
    MemFoo *p3 = new(100) MemFoo;
    MemFoo *p4 = new(100, 'a') MemFoo;
    MemFoo *p5 = new MemFoo(5);
    MemFoo *p6 = new(&start) MemFoo(6);
    MemFoo *p7 = new(100) MemFoo(7);
    MemFoo *p8 = new(100, 'a') MemFoo(8);
    cout << "***************************************" << endl;
    delete p1;
    // delete p3;
    cout << "=======================================" << endl;
}

int operator_test(int argc, char *argv[]) {
    cout << "sizeof(Foo) " << sizeof(MemFoo) << endl;
    
#if 0
    MemFoo *p = ::new MemFoo(7);
    ::delete p;

    MemFoo *arr = ::new MemFoo[5];
    ::delete[] arr;
#else 
    MemFoo *p = new MemFoo(7);
    delete p;

    MemFoo *arr = new MemFoo[5];
    delete[] arr;
#endif 
    
    test_operator_new();
    return 0;
}