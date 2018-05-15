#ifndef SCHED_POLICY_SJF_H_
#define SCHED_POLICY_SJF_H_

#include "sched_context.h"

void InitCtx_SJF(SchedCtx *ctx);
pid_t NextPs_SJF(SchedCtx *ctx, int *terminated);
void FreeInternalCtx_SJF(void *__ctx);

#endif