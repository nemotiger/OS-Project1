#include "psjf.h"

#include <stdlib.h>
#include "priority_queue.h"

typedef struct {
    int finish_time; /* current running process's finsh time */
    void *pqueue;
    /* i = next ready process */
} Ctx;

static int Cmp(const void *lhs, const void *rhs) {
    if((*(const PsInfo**)lhs)->exec_time < (*(const PsInfo**)rhs)->exec_time)
        return -1;
    else if((*(const PsInfo**)lhs)->exec_time == (*(const PsInfo**)rhs)->exec_time)
        return 0;
    else 
        return 1;
}

void InitCtx_PSJF(SchedCtx *ctx) {
    ctx->NextPs = NextPs_PSJF;
    ctx->FreeInternalCtx = FreeInternalCtx_PSJF;
    ctx->__ctx = malloc(sizeof(Ctx));
    ((Ctx*)ctx->__ctx)->pqueue = NewPQueue(ctx->n_ps, Cmp);
    ((Ctx*)ctx->__ctx)->finish_time = -1;
}

void FreeInternalCtx_PSJF(void *__ctx) {
    FreePQueue(((Ctx*)__ctx)->pqueue);
    free(__ctx);
}

pid_t NextPs_PSJF(SchedCtx *ctx, int *terminated) {
    ++ctx->time;
    void *pqueue = ((Ctx*)ctx->__ctx)->pqueue;
    int *finish_time = &((Ctx*)ctx->__ctx)->finish_time;
    *terminated = 0;

    if(*finish_time == ctx->time) {
        *terminated = 1;
        *finish_time = -1;
        PQueuePop(pqueue);
    }

    PsInfo *ps;

    if(ctx->i < ctx->n_ps && ctx->ps[ctx->i].ready_time == ctx->time) {
        if(*finish_time >= 0) {
            ps = PQueueFront(pqueue);
            ps->exec_time = *finish_time - ctx->time;
        }

        while(ctx->i < ctx->n_ps && ctx->ps[ctx->i].ready_time == ctx->time) {
            PQueuePush(pqueue, ctx->ps + ctx->i);
            ++ctx->i;
        }
    }
    else {
        if(*finish_time >= 0) {
            ps = PQueueFront(pqueue);
            return ps->pid;
        }
        if(PQueueEmpty(pqueue)) {
            *finish_time = -1;
            return -1;
        }
    }

    ps = PQueueFront(pqueue);
    *finish_time = ctx->time + ps->exec_time;
    ps->exec_time = -1;
    return ps->pid;
}