#include "sjf.h"

void InitCtx_SJF(SchedCtx *ctx) {
    ctx->NextPs = NextPs_SJF;
}

pid_t NextPs_SJF(SchedCtx *ctx, int *terminated) {
    
}