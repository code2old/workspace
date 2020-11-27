#include<stdio.h>
#include<unistd.h>
#include "log.h"
#include "cpu.h"

namespace utils {

int CPU::getMaxNum() {
    return sysconf(_SC_NPROCESSORS_CONF);
}

int CPU::getOnlineNum() {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

double CPU::getUseRate(int durtime) {
    cpu_info_t info1 = { 0 };
    cpu_info_t info2 = { 0 };
    getOccupy(&info1);
    sleep(durtime);
    getOccupy(&info2);
    return calcUseRate(&info1, &info2);
}

/*从/proc/stat文件中获取cpu的相关信息*/
void CPU::getOccupy(cpu_info_t *info) {
    FILE *fp = NULL;
    char buf[256] = { 0 };
    fp = fopen("/proc/stat", "r");
    fgets(buf, sizeof(buf), fp);
    sscanf(buf, "%s %u %u %u %u %u %u %u", info->name, &info->user, &info->nice, &info->system, &info->idle, &info->iowait, &info->irq, &info->softirq);
    fclose(fp);
}

/*计算CPU使用率*/
double CPU::calcUseRate(cpu_info_t *oldInfo, cpu_info_t *newInfo) {
    double od, nd;
    double usr_dif, sys_dif, nice_dif;
    double user_cpu_rate;
    double kernel_cpu_rate;
    od = (double)(oldInfo->user +oldInfo->nice + oldInfo->system + oldInfo->idle + oldInfo->iowait + oldInfo->irq + oldInfo->softirq);
    nd = (double)(newInfo->user +newInfo->nice + newInfo->system + newInfo->idle + newInfo->iowait + newInfo->irq + newInfo->softirq);
    if (nd - od) {
        user_cpu_rate = (newInfo->user - oldInfo->user)       / (nd - od) * 100;
        kernel_cpu_rate = (newInfo->system - oldInfo->system) / (nd - od) * 100;
        return user_cpu_rate + kernel_cpu_rate;
    }
    return 0;
}

}