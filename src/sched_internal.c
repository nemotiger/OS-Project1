#include "sched_internal.h"

#include <stdlib.h>
#include "sched_context.h"
#include "sched_policy/sched_policy.h"

void *InitScheduler(const char *policy, PsInfo *ps, int n_ps) {
    SchedCtx *ctx = malloc(sizeof(SchedCtx));
    ctx->ps = ps;
    ctx->n_ps = n_ps;
    ctx->time = -1;
    ctx->i = 0;
    ctx->__ctx = NULL;
    ctx->NextPs = NULL;
    ctx->FreeInternalCtx = NULL;

    if(strcmp(policy, "FIFO") == 0)
        InitCtx_FIFO(ctx);
    else if(strcmp(policy, "SJF") == 0)
        InitCtx_SJF(ctx);
    else if(strcmp(policy, "PSJF") == 0)
        InitCtx_PSJF(ctx);
    else
        InitCtx_RR(ctx);

    return ctx;
}

void FreeScheduler(void *sched_ctx) {
    ((SchedCtx*)sched_ctx)->FreeInternalCtx(((SchedCtx*)sched_ctx)->__ctx);
    free(sched_ctx);
}

pid_t SchedNextPs(void *sched_ctx, int *terminated) {
    return ((SchedCtx*)sched_ctx)->NextPs(sched_ctx, terminated);
}