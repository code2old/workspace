#ifndef UTILS_KFIFO_BUFFER_H_
#define UTILS_KFIFO_BUFFER_H_

namespace utils {

class KFifoBuffer {
public:
    KFifoBuffer(int size);
    virtual ~KFifoBuffer();

    bool init();
    unsigned int put(const unsigned char *buffer, unsigned int len);
    unsigned int get(unsigned char *buffer, unsigned int len);

    inline void clean() { 
        _in = _out = 0; 
    }
    inline unsigned int getDataLen() const {
        return _in - _out;
    }
    inline unsigned int getFreeLen() const {
        return _size - ( _in - _out);
    }

private:
    unsigned char *_buffer; /*the buffer holding the data*/
    unsigned int   _size;   /*the size of the allocated buffer*/
    unsigned int   _in;     /*data is added at offset (in % size)*/
    unsigned int   _out;    /*data is extracted from off. (out % size)*/
};

}

#endif 