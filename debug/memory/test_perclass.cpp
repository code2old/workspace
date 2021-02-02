#include <cstddef>
#include <iostream>
#include "memory_test.h"

class Screen {
public:
    Screen(int x): i(x) {}
    int get() { return i; }

    void *operator new(size_t);
    void operator delete(void *, size_t);
private:
    Screen *next;
    static Screen *freeStore;
    static const int screenChunk;
private:
    int i;
};

Screen *Screen::freeStore = 0;
const int Screen::screenChunk = 24;

void *Screen::operator new(size_t size) {
    Screen *p;
    if (!freeStore) {
        /*linked list是空的，所以申请一大块内存*/
        size_t chunk = screenChunk * size;
        freeStore = p = reinterpret_cast<Screen *>(new char[chunk]);
        /*将一大块内存分割，当作linked list串联起来*/
        for (; p!= &freeStore[screenChunk - 1]; ++p) {
            p->next = p + 1;
        }
        p->next = 0;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

void Screen::operator delete(void *p, size_t size) {
    /*将deleted指回free list前端*/
    (static_cast<Screen *>(p))->next = freeStore;
    freeStore = static_cast<Screen *>(p);
}

int perclass_test(int argc, char *argv[]) {
    size_t const N = 100;
    Screen *p[N] = { 0 };
    for (int i = 0; i < N; ++i) {
        p[i] = new Screen(i);
    }
    for (int i = 0; i < N; ++i) {
        cout << p[i]->get() << ": " << p[i] << endl;
    }
    for (int i = 0; i < N; ++i) {
        delete p[i];
    }
    cout << sizeof(Screen) << endl;
    return 0;
}