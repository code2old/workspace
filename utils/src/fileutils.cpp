#include <sys/stat.h>
#include "fileutils.h"

namespace utils {

bool fileutils::exists(const char *filename) {
    struct stat st;
    return (stat(filename, &st) == 0);
}

}