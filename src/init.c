#include <stdlib.h>
#include <string.h>
#include <ctx.h>

#define STACK_SIZE      8192
#define MEMORY_SIZE     32768

mush_ctx* mush_init(void)
{
    mush_ctx* ctx;

    ctx = malloc(sizeof(mush_ctx));
    memset(ctx, 0, sizeof(mush_ctx));

    ctx->memory_size = STACK_SIZE;
    ctx->memory_capacity = MEMORY_SIZE;
    ctx->memory = malloc(MEMORY_SIZE);
    ctx->regs.rip = STACK_SIZE;
    ctx->regs.rsp = STACK_SIZE;
    ctx->regs.rbp = STACK_SIZE;

    return ctx;
}

void mush_quit(mush_ctx* ctx)
{
    free(ctx->memory);
    free(ctx);
}
