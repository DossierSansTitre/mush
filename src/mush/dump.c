#include <stdio.h>
#include <ctx.h>

void mush_dump(mush_ctx* ctx)
{
    puts("- Registers ----------------------------");
    for (size_t i = 0; i < 254; ++i)
    {
        printf(" r%lu:\t0x%016llx", i, ctx->regs.r[i]);
        if (i % 4 == 3)
            printf("\n");
        else
            printf("\t");
    }
    printf(" rsp:\t0x%016llx\t", ctx->regs.rsp);
    printf(" rbp:\t0x%016llx\n", ctx->regs.rbp);
    printf(" rip:\t0x%016llx\n", ctx->regs.rip);
    puts("----------------------------------------");
}
