#include "allocator_test.h"

void *DebugAllocator::allocate(size_t size) {
    obj *p;
    if (!freeStore) {
        /*linked list�ǿյģ���������һ����ڴ�*/
        size_t chunk = CHUNK * size;
        freeStore = p = (obj*)malloc(chunk);
        /*��һ����ڴ�ָ����linked list��������*/
        for (int i = 0; i < (CHUNK - 1); ++i) {
            p->next = (obj*)((char *)p + size);
            p = p->next;
        }
        p->next = nullptr;
    }
    p = freeStore;
    freeStore = freeStore->next;
    return p;
}

void DebugAllocator::deallocate(void *p, size_t size) {
    ((obj*)p)->next = freeStore;
    freeStore = (obj*)p;
}