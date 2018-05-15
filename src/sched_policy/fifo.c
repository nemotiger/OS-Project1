#include "fifo.h"

#include <stdlib.h>
#include "queue.h"

typedef struct {
    int finish_time; /* current running process's finish time, if finish_time < 0 => no process running */
    void *queue;
    /* i = next ready process */
} Ctx;

void InitCtx_FIFO(SchedCtx *ctx) {
    ctx->NextPs = NextPs_FIFO;
    ctx->FreeInternalCtx FreeInternalCtx_FIFO;
    ctx->__ctx = malloc(sizeof(Ctx));
    ((Ctx*)ctx->__ctx)->finish_time = -1;
    ((Ctx*)ctx->__ctx)->queue = NewQueue(ctx->n_ps);
}

void FreeInternalCtx_FIFO(void *__ctx) {
    FreeQueue(((Ctx*)__ctx)->queue);
    free(__ctx);
}

pid_t NextPs_FIFO(SchedCtx *ctx, int *terminated) {
    ++ctx->time;
    int *finish_time = &((Ctx*)ctx->__ctx)->finish_time;
    void *queue = ((Ctx*)ctx->__ctx)->queue;
    *terminated = 0;

    while(ctx->ps[ctx->i].ready_time == ctx->time) {
        QueuePush(queue, ctx->ps + ctx->i);
        ++ctx->i;
    }

    PsInfo *ps;
    if(ctx->time == *finish_time) {
        QueuePop(queue);
        *terminated = 1;
    }
    else if(*finish_time >= 0) {
        ps = QueueFront(queue);
        return ps->pid;
    }

    if(QueueEmpty(queue)) {
        *finish_time = -1;
        return -1;
    }
    else {
        ps = QueueFront(queue);
        *finish_time = ctx->time + ps->exec_time;
        return ps->pid;
    }
}