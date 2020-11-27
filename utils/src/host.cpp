#include <unistd.h>
#include "host.h"

namespace utils {

int Host::getName(char *name, size_t len) {
    int ret = gethostname(name, len);
    return ret;
}

}