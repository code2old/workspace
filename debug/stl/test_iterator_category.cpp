#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>

#include <stack>
#include <queue>

#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <typeinfo>

#include "stl_test.h"

using namespace std;

void _display_category(random_access_iterator_tag it) {
    cout << "random_access_iterator" << endl;
}

void _display_category(bidirectional_iterator_tag it) {
    cout << "bidirectional_iterator" << endl;
}

void _display_category(forward_iterator_tag it) {
    cout << "forward_iterator" << endl;
}

void _display_category(input_iterator_tag it) {
    cout << "input_iterator" << endl;
}

void _display_category(output_iterator_tag it) {
    cout << "output_iterator" << endl;
}

template <typename I>
void display_category(I iter) {
    typename iterator_traits<I>::iterator_category cagy;
    _display_category(cagy);
    cout << "typeid(iter).name() = " << typeid(iter).name() << endl << endl;
}

int iterator_category_test(int argc, char *argv[]) {
    cout << "\ntest_iterator_category()......\n";
    display_category(array<int, 10>::iterator());
    display_category(vector<int>::iterator());
    display_category(list<int>::iterator());
    display_category(forward_list<int>::iterator());
    display_category(deque<int>::iterator());

    display_category(set<int>::iterator());
    display_category(map<int, int>::iterator());
    display_category(unordered_set<int>::iterator());
    display_category(unordered_map<int, int>::iterator());
    return 0;
}
