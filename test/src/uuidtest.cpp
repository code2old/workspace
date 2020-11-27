#include <stdio.h>

#include "log.h"
#include "test.h"
#include "uuid.h"
#include "thread.h"
#include "runnable.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <bitset>

using namespace std;

class UidTest: public utils::Runnable {
public:
    void start() {
        thread.start(this, NULL);
    }
    void run(utils::CThread *thread, void *arg) {
        uint64_t uuid = utils::uuid::generate();
        LOG(INFO, "tid: %lu, uuid: %llu", pthread_self(), uuid);
    }
private:
    utils::CThread thread;
};

int test_uuid(int argc, char *argv[]) {
    UidTest *uid = new UidTest[2];
    for (int i=0; i<2; ++i) {
        uid[i].start();
    }
    sleep(1);
    return 0;
}