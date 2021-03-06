#ifndef UTILS_STRINGUTIL_H_
#define UTILS_STRINGUTIL_H_

#include <string>
#include <vector>

namespace utils {

class stringutils {
public:
    static std::vector<std::string> split(const std::string& s, const char *delim);
};

}

#endif 