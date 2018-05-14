#include "round_robin.h"

void InitCtx_RR(SchedCtx *ctx) {
    ctx->NextPs = NextPs_RR;
}

pid_t NextPs_RR(SchedCtx *ctx, int *terminated) {
    
}