#include "psjf.h"

#include <stdlib.h>

typedef struct {
    int rq_end; /* ready queue end */
    int finish_time; /* current running process's finsh time */
} Ctx;

static int Cmp(const void *lhs, const void *rhs) {
    if(((const PsInfo_Sched*)lhs)->exec_time < ((const PsInfo_Sched*)rhs)->exec_time)
        return -1;
    else if(((const PsInfo_Sched*)lhs)->exec_time == ((const PsInfo_Sched*)rhs)->exec_time)
        return 0;
    else 
        return 1;
}

void InitCtx_PSJF(SchedCtx *ctx) {
    ctx->NextPs = NextPs_PSJF;
    ctx->__ctx = malloc(sizeof(Ctx));
    ((Ctx*)ctx->__ctx)->rq_end = 0;
    ((Ctx*)ctx->__ctx)->finish_time = -1;
    /* i = ready queue start */
}

pid_t NextPs_PSJF(SchedCtx *ctx, int *terminated) {
    ++ctx->time;
    int *rq_end = &((Ctx*)ctx->__ctx)->rq_end;
    int *finish_time = &((Ctx*)ctx->__ctx)->finish_time;
    
    *terminated = 0;
    if(*finish_time == ctx->time)
        *terminated = 1;

    int k;
    
    if(*rq_end != ctx->n_ps && ctx->ps[*rq_end].ready_time == ctx->time) {
        for(k = *rq_end; k < ctx->n_ps; ++k) {
            if(ctx->ps[k].ready_time != ctx->time)
                break;
        }
        *rq_end = k;

        if(*finish_time > ctx->time)
            ctx->ps[--ctx->i].exec_time = *finish_time - ctx->time;
            
        qsort(ctx->ps + ctx->i, *rq_end - ctx->i, sizeof(PsInfo_Sched), Cmp);
        *finish_time = ctx->time + ctx->ps[ctx->i].exec_time;
        return *(ctx->ps[ctx->i++].pid);
    }
    else {
        if(*finish_time > ctx->time)
            return *(ctx->ps[ctx->i - 1].pid);
        
        if(ctx->i == *rq_end) {
            *finish_time = -1;
            return -1;
        }
        else {
            *finish_time = ctx->time + ctx->ps[ctx->i].exec_time;
            return *(ctx->ps[ctx->i ++].pid);
        }
    }
}