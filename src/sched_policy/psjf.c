#include "psjf.h"

void InitCtx_PSJF(SchedCtx *ctx) {
    ctx->NextPs = NextPs_PSJF;
}

pid_t NextPs_PSJF(SchedCtx *ctx, int *terminated) {
    
}