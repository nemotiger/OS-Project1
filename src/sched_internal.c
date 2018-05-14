#include "sched_internal.h"

#include <stdlib.h>
#include "sched_context.h"
#include "sched_policy/sched_policy.h"

void *InitScheduler(const char *policy, const PsInfo *ps, int n_ps) {
    SchedCtx *ctx = malloc(sizeof(SchedCtx));
    PsInfo_Sched *psinfo_sched = malloc(n_ps * sizeof(PsInfo_Sched));

    for(int i = 0; i < n_ps; ++i) {
        psinfo_sched[i].ready_time = ps[i].ready_time;
        psinfo_sched[i].exec_time = ps[i].exec_time;
        psinfo_sched[i].pid = &ps[i].pid;
    }

    ctx->ps = psinfo_sched;
    ctx->n_ps = n_ps;
    ctx->time = -1;
    ctx->i = 0;
    ctx->NextPs = NULL;
    ctx->__ctx = NULL;

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
    free(((SchedCtx*)sched_ctx))->ps);
    free(((SchedCtx*)sched_ctx))->__ctx);
    free(sched_ctx);
}

pid_t SchedNextPs(void *sched_ctx, int *terminated) {
    return ((SchedCtx*)sched_ctx)->NextPs(sched_ctx, terminated);
}