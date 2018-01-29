#include <ctx.h>

static void vm_run_inst(mush_ctx* ctx)
{
    char* iptr;
    char reg1;
    char reg2;
    uint64_t imm;

    iptr = ctx->memory + ctx->regs.rip;

    switch (*iptr++)
    {
    /* NOP */
    case 0x00:
        ctx->regs.rip++;
        break;

    /* MOV r/r */
    case 0x01:
        reg1 = *iptr++;
        reg2 = *iptr++;
        ctx->regs.r[reg1] = ctx->regs.r[reg2];
        ctx->regs.rip += 3;
        break;

    /* MOV r/imm64 */
    case 0x02:
        reg1 = *iptr++;
        imm = *(uint64_t*)iptr;
        ctx->regs.r[reg1] = imm;
        ctx->regs.rip += 10;
        break;

    /* MOV r/imm32 */
    case 0x03:
        reg1 = *iptr++;
        imm = *(uint32_t*)iptr;
        ctx->regs.r[reg1] = imm;
        ctx->regs.rip += 6;
        break;

    /* MOV r/imm16 */
    case 0x04:
        reg1 = *iptr++;
        imm = *(uint16_t*)iptr;
        ctx->regs.r[reg1] = imm;
        ctx->regs.rip += 4;
        break;

    /* MOV r/imm8 */
    case 0x05:
        reg1 = *iptr++;
        imm = *(uint8_t*)iptr;
        ctx->regs.r[reg1] = imm;
        ctx->regs.rip += 3;
        break;
    }
}

void mush_vm_run(mush_ctx* ctx)
{
    for (;;)
    {
        vm_run_inst(ctx);
        return;
    }
}
