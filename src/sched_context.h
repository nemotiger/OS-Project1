#ifndef SCHED_CONTEXT_H_
#define SCHED_CONTEXT_H_

#include "ps_info.h"

/* Scheduler Context */
struct _SchedCtx {
    /* ps : pointer to a list of PsInfo that is sorted by ready_time 
     * ps should not own the underlying list.
     * The order of PsInfo in the list should not be changed.
     * The fields in PsInfo should not be modified except ps[i]->exec_time can be modified if ps[i]->ready_time <= sched_ctx->time 
     */
    PsInfo *ps;
    int n_ps; /* number of processes */
    int time;
    int i; /* usage: implementation defined */
    void *__ctx; /* internal context, implementation defined */

    pid_t (*NextPs)(struct _SchedCtx *sched_ctx, int *terminated); /* should be bound to NextPs_{policy} */
    void (*FreeInternalCtx)(void *__ctx); /* should be bound to FreeInternalCtx_{policy} */
};
typedef struct _SchedCtx SchedCtx;

#endif