#include "stl_test.h"

int hash_test(int argc, char *argv[]) {
    void *pi = (void *)(new int(100));
    cout << hash<int>()(123) << endl;
    cout << hash<long>()(123L) << endl;
    cout << hash<string>()(string("Ace")) << endl;
    cout << hash<const char *>()("Ace") << endl;
    cout << hash<char>()('A') << endl;
    return 0;
}