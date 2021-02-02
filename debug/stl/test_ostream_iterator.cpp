#include "stl_test.h"

int ostream_iterator_test(int argc, char *argvp[]) {
    vector<int> myvector;
    for (int i = 0; i < 10; ++i) {
        myvector.push_back(i * 10);
    }
    ostream_iterator<int> out_it(std::cout, ",");
    copy(myvector.begin(), myvector.end(), out_it);
    return 0;
}