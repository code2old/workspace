#ifndef UTILS_HOSTINFO_H_
#define UTILS_HOSTINFO_H_

#include <stdio.h>

namespace utils {

class Host {
public:
    static int getName(char *name, size_t len);
};

}

#endif 