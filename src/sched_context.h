#ifndef SCHED_CONTEXT_H_
#define SCHED_CONTEXT_H_

#include <sys/types.h>

/* Process Info for scheduler */
typedef struct {
    int ready_time;
    int exec_time;
    const pid_t *pid;
} PsInfo_Sched;

/* Scheduler Context */
struct _SchedCtx {
    PsInfo_Sched *ps;
    int n_ps;
    pid_t (*NextPs)(struct _SchedCtx *sched_ctx, int *terminated);
    int time;
    void *__ctx;
};
typedef struct _SchedCtx SchedCtx;

#endif