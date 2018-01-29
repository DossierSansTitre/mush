#include <mush/mush.h>

#include <ctx.h>

void mush_vm_run(void*);

int main(int argc, char **argv)
{
    mush_ctx* ctx;

    ctx = mush_init();
    mush_dump(ctx);
    ctx->memory[0x2000] = 0x02;
    ctx->memory[0x2001] = 0x02;
    ctx->memory[0x2002] = 0x12;
    ctx->memory[0x2003] = 0x34;
    ctx->memory[0x2004] = 0x56;
    ctx->memory[0x2005] = 0x78;
    ctx->memory[0x2006] = 0x9a;
    ctx->memory[0x2007] = 0xbc;
    ctx->memory[0x2008] = 0xde;
    ctx->memory[0x2009] = 0xff;
    mush_vm_run(ctx);
    mush_dump(ctx);
    mush_quit(ctx);
    return 0;
}
