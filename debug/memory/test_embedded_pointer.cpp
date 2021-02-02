#include "memory_test.h"

class EmbeddedPointer {
public:
    struct obj {
        struct obj *next;
    };

    int m_i;
    int m_j;
    int m_k;
};

int embedded_pointer_test(int argc, char *argv[]) {
    EmbeddedPointer p1;
    p1.m_i = 1;
    p1.m_j = 2;
    p1.m_k = 3;
    cout << sizeof(p1) << endl;
    EmbeddedPointer::obj *temp;
    temp = (EmbeddedPointer::obj *)&p1;
    temp->next = nullptr;
    cout << p1.m_i << ": " << p1.m_j << ": " << p1.m_k << endl;
    return 0;

}