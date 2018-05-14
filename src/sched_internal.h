#ifndef SCHED_INTERNAL_H_
#define SCHED_INTERNAL_H_

#include <sys/types.h>

/* Process Info */
typedef struct {
    char name[32];
    int ready_time;
    int exec_time;
    pid_t pid;
} PsInfo;

void *InitScheduler(const char *policy, const PsInfo *ps, int n_ps);
void FreeScheduler(void *sched_ctx);
pid_t SchedNextPs(void *sched_ctx, int *terminated);



#endif