#include <sys/stat.h>

#include "fileutil.h"

bool isFileExist(const char *filename) {
    struct stat st;
    return (stat(filename, &st) == 0);
}