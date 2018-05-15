#ifndef SCHED_INTERNAL_H_
#define SCHED_INTERNAL_H_

#include "ps_info.h"

void *InitScheduler(const char *policy, PsInfo *ps, int n_ps);
void FreeScheduler(void *sched_ctx);
pid_t SchedNextPs(void *sched_ctx, int *terminated);



#endif