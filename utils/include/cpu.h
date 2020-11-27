#ifndef UTILS_CPU_INFO_H_
#define UTILS_CPU_INFO_H_

#include "singleton.h"

namespace utils {

/*cpu_info_t结构体存放CPU相关信息*/
typedef struct _cpu_info {
    char name[20];
    unsigned int user;
    unsigned int nice;
    unsigned int system;
    unsigned int idle;
    unsigned int iowait;
    unsigned int irq;
    unsigned int softirq;
} cpu_info_t;

class CPU : public utils::Singleton<CPU> {
public:
    int getMaxNum();
    int getOnlineNum();
    double getUseRate(int durtime);
private:
    void getOccupy(cpu_info_t *info);
    double calcUseRate(cpu_info_t *oldInfo, cpu_info_t *newInfo);
};

}

#endif 