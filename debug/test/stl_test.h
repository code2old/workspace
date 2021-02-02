#ifndef STL_TEST_H_
#define STL_TEST_H_

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <bitset>
#include <tuple>

using namespace std;

extern int iterator_category_test(int argc, char *argv[]);
extern int bind_test(int argc, char *argv[]);
extern int ostream_iterator_test(int argc, char *argvp[]);
extern int istream_iterator_test(int argc, char *argv[]);
extern int nullptr_test(int argc, char *argv[]);
extern int auto_test(int argc, char *argv[]);
extern int initializer_list_test(int argc, char *argv[]);
extern int default_test(int argc, char *argv[]);
extern int alias_template_test(int argc, char *argv[]);
extern int lambdas_test(int argc, char *argv[]);
extern int variadic_template_test(int argc, char *argv[]);
extern int rvalue_references_test(int argc, char *argv[]);
extern int hash_test(int argc, char *argv[]);

#endif 