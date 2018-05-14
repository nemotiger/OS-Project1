#include "fifo.h"

typedef struct {
    int i; /* current process index */
    int finish_time; /* current running process's finish time, if finish_time < 0 => no process running*/
} Ctx;

void InitCtx_FIFO(SchedCtx *ctx) {
    ctx->NextPs = NextPs_FIFO;
    ctx->__ctx = malloc(sizeof(Ctx));
    ((Ctx*)ctx->__ctx)->i = 0;
    ((Ctx*)ctx->__ctx)->finish_time = -1;
}

pid_t NextPs_FIFO(SchedCtx *ctx, int *terminated) {
    ++ctx->time;
    Ctx *__ctx = ctx->__ctx;
    *terminated = 0;

    if(__ctx->finish_time < 0) {
        if(ctx->ps[__ctx->i].ready_time == ctx->time) {
            __ctx->finish_time = ctx->time + ctx->ps[__ctx->i].exec_time;
            return *(ctx->ps[__ctx->i].pid);
        }
        else
            return -1;
    }
    else {
        if(__ctx->finish_time == ctx->time) {
            *terminated = 1;
            ++__ctx->i;
            if(ctx->ps[__ctx->i].ready_time == ctx->time) {
                __ctx->finish_time = ctx->time + ctx->ps[__ctx->i].exec_time;
                return *(ctx->ps[__ctx->i].pid);
            }
            else {
                __ctx->finish_time = -1;
                return -1;
            }
        }
        else
            return *(ctx->ps[i].pid);
    }
}