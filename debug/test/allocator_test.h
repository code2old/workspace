#ifndef DEBUG_TEST_ALLOCATOR_H_
#define DEBUG_TEST_ALLOCATOR_H_

#include <malloc.h>

class DebugAllocator {
private:
    struct obj {
        struct obj *next;
    };
public:
    void *allocate(size_t size);
    void deallocate(void *p, size_t size);
private:
    obj *freeStore = nullptr;
    const int CHUNK = 5;
};

#define DECLARE_POOL_ALLOC() \
public: \
void *operator new (size_t size) { return allocator.allocate(size); }   \
void operator delete(void *p, size_t size) { return allocator.deallocate(p, size); }   \
protected:  \
    static DebugAllocator allocator;

#define IMPLEMENT_POOL_ALLOC(className) \
DebugAllocator className::allocator;

#endif 