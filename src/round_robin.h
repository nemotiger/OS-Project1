#ifndef ROUND_ROBIN_H_
#define ROUND_ROBIN_H_

#include "sched_context.h"

void InitCtx_RR(SchedCtx *ctx);
pid_t NextPs_RR(SchedCtx *ctx, int *terminated);
void FreeInternalCtx_RR(void *__ctx);

#endif