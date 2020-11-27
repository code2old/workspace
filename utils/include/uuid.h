#ifndef UTILS_UUID_H_
#define UTILS_UUID_H_

#include <atomic>
#include <stdint.h>

namespace utils {

class uuid {
public:
    /*twitter snowflake算法*/
    /*64     63----------------22-----------12-----------0*/
    /*符号位 |     41位时间     | 10位机器码 | 12位自增码 | */
    uuid();
    ~uuid();

    static void setEpoch(uint64_t epoch);
    static void setMachine(int32_t machine);
    static int64_t generate(void);

private:
    static uint64_t _epoch;
    static uint64_t _time;
    static int32_t  _machine;
    static std::atomic<int32_t>  _sequence;
};

}

#endif 