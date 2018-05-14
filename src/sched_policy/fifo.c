#include "fifo.h"

#include <stdlib.h>

typedef struct {
    int finish_time; /* current running process's finish time, if finish_time < 0 => no process running*/
} Ctx;

void InitCtx_FIFO(SchedCtx *ctx) {
    ctx->NextPs = NextPs_FIFO;
    ctx->__ctx = malloc(sizeof(Ctx));
    ((Ctx*)ctx->__ctx)->finish_time = -1;
}

pid_t NextPs_FIFO(SchedCtx *ctx, int *terminated) {
    ++ctx->time;
    int *finish_time = &((Ctx*)ctx->__ctx)->finish_time;
    *terminated = 0;

    if(*finish_time < 0) {
        if(ctx->ps[ctx->i].ready_time == ctx->time) {
            *finish_time = ctx->time + ctx->ps[ctx->i].exec_time;
            return *(ctx->ps[ctx->i].pid);
        }
        else
            return -1;
    }
    else {
        if(*finish_time == ctx->time) {
            *terminated = 1;
            ++ctx->i;
            if(ctx->ps[ctx->i].ready_time == ctx->time) {
                *finish_time = ctx->time + ctx->ps[ctx->i].exec_time;
                return *(ctx->ps[ctx->i].pid);
            }
            else {
                *finish_time = -1;
                return -1;
            }
        }
        else
            return *(ctx->ps[ctx->i].pid);
    }
}