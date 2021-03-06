#ifndef PSJF_H_
#define PSJF_H_

#include "sched_context.h"

void InitCtx_PSJF(SchedCtx *ctx);
pid_t NextPs_PSJF(SchedCtx *ctx, int *terminated);
void FreeInternalCtx_PSJF(void *__ctx);

#endif