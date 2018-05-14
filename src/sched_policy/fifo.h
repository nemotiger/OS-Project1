#ifndef SCHED_POLICY_FIFO_H_
#define SCHED_POLICY_FIFO_H_

#include "sched_context.h"

void InitCtx_FIFO(SchedCtx *ctx);
pid_t NextPs_FIFO(SchedCtx *ctx, int *terminated);

#endif