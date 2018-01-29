#include <stdio.h>
#include <ctx.h>

void mush_dump(mush_ctx* ctx)
{
    puts("- Registers ----------------------------");
    for (size_t i = 0; i < 14; ++i)
    {
        printf(" r%lu:\t0x%016llx\n", i, ctx->regs.r[i]);
    }
    printf(" rsp:\t0x%016llx\n", ctx->regs.rsp);
    printf(" rbp:\t0x%016llx\n", ctx->regs.rbp);
    printf(" rip:\t0x%016llx\n", ctx->regs.rip);
    puts("----------------------------------------");
}
