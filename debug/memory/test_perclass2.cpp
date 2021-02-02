#include "memory_test.h"

class Airplane {
public:
    unsigned long getMiles() {
        return rep.miles;
    }
    char getType() {
        return rep.type;
    }
    void set(unsigned long m, char t) {
        rep.miles = m;
        rep.type = t;
    }
public:
    static void *operator new(size_t size);
    static void operator delete(void *p, size_t size);

private:
    struct AirplaneRep {
        unsigned int miles;
        char type;
    };
private:
    union {
        AirplaneRep rep;
        Airplane   *next;
    };
private:
    static const int BLOCK_SIZE;
    static Airplane *headOfFreeList;
};

const int Airplane::BLOCK_SIZE = 512;
Airplane *Airplane::headOfFreeList = 0;

void *Airplane::operator new(size_t size) {
    /*�����С����ת����::operator new()*/
    if (size != sizeof(Airplane)) {
        return ::operator new(size);
    }
    Airplane *p = headOfFreeList;
    if (p) {
        /*���p��Ч���Ͱ�listͷ������һ��Ԫ��*/
        headOfFreeList = p->next;
    }
    else {
        /*free list�ѿգ�����һ����ڴ�*/
        Airplane *newBlock = static_cast<Airplane*>(::operator new(BLOCK_SIZE * sizeof(Airplane)));
        /*��С�鴮��һ��free list*/
        for (int i = 1; i < BLOCK_SIZE; ++i) {
            newBlock[i].next = &newBlock[i + 1];
        }
        newBlock[BLOCK_SIZE - 1].next = 0;
        p = newBlock;
        headOfFreeList = &newBlock[1];
    }
    return p;
}

void Airplane::operator delete(void *p, size_t size) {
    if (0 == p) {
        return;
    }
    if (size != sizeof(Airplane)) {
        ::operator delete(p);
        return;
    }
    Airplane *carcass = static_cast<Airplane*>(p);
    carcass->next = headOfFreeList;
    headOfFreeList = carcass;
}

int perclass2_test(int argc, char *argv[]) {
    cout << sizeof(Airplane) << endl;
    size_t const N = 3;
    Airplane *p[N] = { 0 };

    for (int i = 0; i < N; ++i) {
        p[i] = new Airplane;
    }
    /*�������object�Ƿ�����*/
    p[1]->set(10, 'A');

    for (int i = 0; i < N; ++i) {
        cout << p[i] << endl;
    }
    for (int i = 0; i < N; ++i) {
        delete p[i];
    }
    return 0;
}