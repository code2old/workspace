#include "memory_test.h"

class Complex {
public:
    Complex(int real, int imag) {
        cout << "Complex()" << endl;
        m_real = real;
        m_imag = imag;
    }
    ~Complex() {
        cout << "~Complex()" << endl;
    }
private:
    int m_real;
    int m_imag;
};


static int newtest() {
    Complex *pc = nullptr;
    try {
        void *mem = operator new(sizeof(Complex));
        pc = static_cast<Complex*>(mem);
        pc->Complex::Complex(1, 2);
    }
    catch (std::bad_alloc) {
        cout << "bad_alloc" << endl;
    }
    pc->~Complex();
    operator delete(pc);
    cout << "test finish" << endl;

    return 0;
}

class MemoryA{
public:
    MemoryA(): id(0) {
        cout << "default ctor.this " << this << " id= " << id << endl;
    }
    MemoryA(int i):id(i) {
        cout << "ctor.this " << this << " id= " << i << endl;
    }
    ~MemoryA() {
        cout << "dtor.this " << this << " id= " << id << endl;
    }
public:
    int id;
};

static void placement_new_test() {
    int size = 3;
    // MemoryA* buf = new MemoryA[size];
    //cout << sizeof(buf) << endl;
    //MemoryA* buf = (MemoryA*)malloc(sizeof(MemoryA)*size);
    // MemoryA *buf = (MemoryA*)new char[sizeof(MemoryA)*size];
    MemoryA *buf = (MemoryA *)new char[sizeof(MemoryA) * size];
    MemoryA* temp = buf;
    cout << "buf=" << buf << " tmp=" << temp << endl;
    for (int i = 0; i < size; ++i) {
        cout << temp + i << '\t';
        MemoryA* test = new (temp + i) MemoryA(i);
        // cout << test << '\t'<< endl;
        //temp++;

    }
    cout << "buf=" << buf << " tmp=" << temp << endl;
    for (int i = 0; i < size; ++i) {
        cout << temp + i << '\t';
        ((MemoryA*)(temp + i))->~MemoryA();
        // cout << test << '\t'<< endl;
        //temp++;
    }
    //free(buf);
    delete[](char*)buf;
}

int memory_test(int argc, char *argv[]) {
    //void *p = malloc(512);
    //free(p);

    //complex<int> *p2 = new complex<int>;
    //delete p2;

    //void *p3 = ::operator new(512);
    //::operator delete(p3);

    //void *p4 = allocator<int>().allocate(7);
    //allocator<int>().deallocate((int*)p4, 7);

    //newtest();
    placement_new_test();

    return 0;
}