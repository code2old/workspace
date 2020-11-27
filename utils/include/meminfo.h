#ifndef UTILS_MEMINFO_H_
#define UTILS_MEMINFO_H_

namespace utils {

typedef struct _mem_info_t {
    char name[20];
    unsigned long total;
    char text[20];
} mem_info_t;

}

#endif 