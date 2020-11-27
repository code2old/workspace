#include "test.h"
#include "log.h"
#include "shell.h"

/* software version */
#define SOFT_MAJOR_VERSION          2U
#define SOFT_MINOR_VERSION 	        0U
#define SOFT_REVISION               0U 
/*
版本:用64位长整型表示。高47～40位:主版本号(MAJOR);39～32:次版本号(MINOR),31~24:修订版本
     23～0:编译时间（23-16:年；15-8:月；7-0:日)
*/
#define MAKE_SOFT_VERSION(_major,_minor,_revision,_year,_month,_day) \
    (\
        ((_major)<<40)\
        |(((_minor)&0xff)<<32)\
        |(((_revision)& 0xff) << 24)\
        |(((_year-2000)&0xf)<<16)\
        |(((_month)&0xf)<<8)\
        |((_day)&0xff)\
    )
    

int getsoftversion(void *ptr, const char *recvbuf, char *sendbuf) {
    int y = 0, m = 0, d = 0;
    char ms[4] = {0};
    const char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    if (std::sscanf(__DATE__, "%s %d %d", ms, &d, &y) <= 0)
    {
        LOG(ERROR, "sscanf error");
        return 0;
    }

    for (m = 0; m < 12; m++)
    {
        if (strcmp(ms, months[m]) == 0)
        {
            break;
        }
    }
    m++;

    if (sendbuf != NULL)
    {
        snprintf(sendbuf, 128, "build:%02d%02d%02d %s V%02d.%02d.%02d\n", y - 2000, m, d, __TIME__, SOFT_MAJOR_VERSION, SOFT_MINOR_VERSION, SOFT_REVISION);
    }

    return (unsigned long long)MAKE_SOFT_VERSION((unsigned long long)SOFT_MAJOR_VERSION, (unsigned long long)SOFT_MINOR_VERSION, SOFT_REVISION, y, m, d);
}

int test_shell(int argc, char *argv[]) {
    utils::ShellServer::getInstance()->init();
    utils::ShellServer::getInstance()->regCmd("getSoftVersion", getsoftversion, NULL);
    while (1) {
        sleep(1);
    }
    return 0;
}