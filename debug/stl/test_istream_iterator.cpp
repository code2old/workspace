#include "stl_test.h"

int istream_iterator_test(int argc, char *argv[]) {
    double value1, value2;
    istream_iterator<double>eos;
    istream_iterator<double>it(cin);
    if (it != eos) {
        value1 = *it;
    }
    ++it;
    if (it != eos) {
        value2 = *it;
    }
    cout << value1 << "*" << value2 << endl;
    return 0;
}