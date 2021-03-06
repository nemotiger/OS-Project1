#include "sjf.h"

#include <stdlib.h>
#include "priority_queue.h"

typedef struct {
    int finish_time; /* current running process's finsh time */
    void *pqueue;
    /* i = next ready process */
} Ctx;

static int Cmp(const void *lhs, const void *rhs) {
    const PsInfo *_lhs = *(const PsInfo**)lhs, *_rhs = *(const PsInfo**)rhs;
    if(_lhs->exec_time < _rhs->exec_time)
        return -1;
    else if(_lhs->exec_time > _rhs->exec_time)
        return 1;
    else {
        if(_lhs->ready_time < _rhs->ready_time)
            return -1;
        else if(_lhs->ready_time == _rhs->ready_time)
            return 0;
        else 
            return 1;
    }
}

void InitCtx_SJF(SchedCtx *ctx) {
    ctx->NextPs = NextPs_SJF;
    ctx->FreeInternalCtx = FreeInternalCtx_SJF;
    ctx->__ctx = malloc(sizeof(Ctx));
    ((Ctx*)ctx->__ctx)->pqueue = NewPQueue(ctx->n_ps, Cmp);
    ((Ctx*)ctx->__ctx)->finish_time = -1;
}

void FreeInternalCtx_SJF(void *__ctx) {
    FreePQueue(((Ctx*)__ctx)->pqueue);
    free(__ctx);
}

pid_t NextPs_SJF(SchedCtx *ctx, int *terminated) {
    ++ctx->time;
    int *finish_time = &((Ctx*)ctx->__ctx)->finish_time;
    void *pqueue = ((Ctx*)ctx->__ctx)->pqueue;
    *terminated = 0;

    while(ctx->i < ctx->n_ps && ctx->ps[ctx->i].ready_time == ctx->time) {
        PQueuePush(pqueue, ctx->ps + ctx->i);
        ++ctx->i;
    }

    PsInfo *ps;

    if(*finish_time == ctx->time) {
        *terminated = 1;
        PQueuePop(pqueue);
    }
    else if(*finish_time >= 0) {
        ps = PQueueFront(pqueue);
        return ps->pid;
    }

    if(PQueueEmpty(pqueue)) {
        *finish_time = -1;
        return -1;
    }
    else {
        ps = PQueueFront(pqueue);
        *finish_time = ctx->time + ps->exec_time;
        ps->exec_time = -1;
        return ps->pid;
    }
}