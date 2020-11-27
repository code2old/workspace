#include <iostream>
#include <string.h>
#include "kfifobuffer.h"

namespace utils {

static inline bool is_power_of_2(unsigned long n) {
    return ((n) && ((n & (n - 1)) == 0));
}

static inline int fls(int x) {
    int r;
    __asm__("bsrl %1,%0\n\t"
        "jnz 1f\n\t"
        "movl $-1,%0\n"
        "1:":"=r"(r):"rm"(x));
    return r+1;
} 

inline unsigned long roundup_power_of_two(unsigned long x) {
    return 1UL << fls(x-1);
}

KFifoBuffer::KFifoBuffer(int size)
    : _buffer(NULL),
      _size(size),
      _in(0),
      _out(0) {
    /*round up to the next power of 2*/
    if (!is_power_of_2(_size)) {
        _size = roundup_power_of_two(_size);
    }
}

KFifoBuffer::~KFifoBuffer() {
    if (_buffer != NULL) {
        delete []_buffer;
        _buffer = NULL;
    }
}

bool KFifoBuffer::init() {
    _buffer = new unsigned char [_size];
    if (!_buffer) {
        return false;
    }
    _in = _out = 0;
    return true;
}

unsigned int KFifoBuffer::put(const unsigned char *buffer, unsigned int len) {
    unsigned int l;
    len = std::min(len, _size - _in + _out);
    /*
     * Ensure that we sampe the _out index -before- we start putting bytes into the KFifoBuffer
     */
    __sync_synchronize();
    /*first put the data starting from fifo->in to buffer end*/
    l = std::min(len, _size - (_in & (_size - 1)));
    memcpy(_buffer + (_in & (_size - 1)), buffer, l);
    /*then put the rest (if any) at the begining of the buffer*/
    memcpy(_buffer, buffer + l, len - l);
    /*
     * Ensure that we add the bytes to kfifo -before- we update the fifo->in index
     */
    __sync_synchronize();
    _in += len;
    return len;
}

unsigned int KFifoBuffer::get(unsigned char *buffer, unsigned int len) {
    unsigned int l;
    len = std::min(len, _in - _out);
    /*
     * Ensure that we sample the fifo->in index -before- we start removing bytes from kfifo
     */
    __sync_synchronize();
    /*first get the data from fifo->out ungil the end of the buffer*/
    l = std::min(len, _size - (_out & (_size - 1)));
    memcpy(buffer, _buffer + (_out & (_size - 1)), l);
    /*then get the rest (if any) from the begining of the buffer*/
    memcpy(buffer+l, _buffer, len - l);
    /*
     * Ensure that we remove the bytes from the kfifo -before- we update the fifo->out index
     */
    __sync_synchronize();
    _out += len;
    return len;
}

}