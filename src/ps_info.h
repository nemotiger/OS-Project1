#ifndef PS_INFO_H_
#define PS_INFO_H_

#include <sys/types.h>

/* Process Info */
typedef struct {
    char name[32];
    int ready_time;
    int exec_time;
    pid_t pid;
} PsInfo;

#endif