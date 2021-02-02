#ifndef DEBUG_MEMORY_TEST_H_
#define DEBUG_MEMORY_TEST_H_

#include <iostream>
#include <complex>
#include <malloc.h>
#include <exception>
#include <cassert>
#include <vector>

using namespace std;

extern int memory_test(int argc, char *argv[]);
extern int operator_test(int argc, char *argv[]);
extern int perclass_test(int argc, char *argv[]);
extern int perclass2_test(int argc, char *argv[]);
extern int allocator_test(int argc, char *argv[]);
extern int embedded_pointer_test(int argc, char *argv[]);
extern int new_handler_test(int argc, char *argv[]);

extern int malloc_test(int argc, char *argv[]);
extern int cookie_test(int argc, char *argv[]);

#endif 