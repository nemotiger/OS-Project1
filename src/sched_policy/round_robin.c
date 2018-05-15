#include "sched_policy/round_robin.h"

#include <stdlib.h>
#include "queue.h"

#define TIME_QUANTUM 500

typedef struct {
    int preempt_time;
    void *queue;
    /* i = next ready process */
} Ctx;

static int Min(int a, int b) {
    return a < b ? a : b;
}

void InitCtx_RR(SchedCtx *ctx) {
    ctx->NextPs = NextPs_RR;
    ctx->__ctx = malloc(sizeof(Ctx));
    ((Ctx*)ctx->__ctx)->preempt_time = -1;
    ((Ctx*)ctx->__ctx)->queue = NewQueue(ctx->n_ps);
}

pid_t NextPs_RR(SchedCtx *ctx, int *terminated) {
    ++ctx->time;
    int *preempt_time = &((Ctx*)ctx->__ctx)->preempt_time;
    void *queue = ((Ctx*)ctx->__ctx)->queue;
    *terminated = 0;

    while(ctx->ps[ctx->i].ready_time == ctx->time) {
        QueuePush(queue, ctx->ps + ctx->i);
        ++ctx->i;
    }

    PsInfo_Sched *ps;
    if(ctx->time == *preempt_time) {
        ps = QueueFront(queue);
        QueuePop(queue);
        if(ps->exec_time > 0)
            QueuePush(queue, ps);
        else
            *terminated = 1;
    }
    else if(*preempt_time >= 0) {
        ps = QueueFront(queue);
        return *ps->pid;
    }

    if(QueueEmpty(queue)) {
        *preempt_time = -1;
        return -1;
    }
    else {
        ps = QueueFront(queue);
        int run_time = Min(ps->exec_time, TIME_QUANTUM);
        *preempt_time = ctx->time + run_time;
        ps->exec_time -= run_time;
        return *ps->pid;
    }
}