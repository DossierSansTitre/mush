#include <string.h>
#include <stdint.h>
#include <stdio.h>

#define A_NONE  0
#define A_REG   1
#define A_IMM8  2
#define A_IMM16 3
#define A_IMM32 4
#define A_IMM64 5

struct mush_op_
{
    const char* mnemo;
    uint8_t     encoding[2];
};

typedef struct mush_op_ mush_op;

static const mush_op mush_op_table[256] = {
    {"NOP"},
    {"MOV", {A_REG, A_REG}},
    {"MOV", {A_REG, A_IMM64}},
    {"MOV", {A_REG, A_IMM32}},
    {"MOV", {A_REG, A_IMM16}},
    {"MOV", {A_REG, A_IMM8}},
};

static const char* mush_reg_table[16] = {
    "r0",
    "r1",
    "r2",
    "r3",
    "r4",
    "r5",
    "r6",
    "r7",
    "r8",
    "r9",
    "r10",
    "r11",
    "r12",
    "r13",
    "rsp",
    "rbp"
};

const void* mush_disasm(char* buffer, const void* iptr)
{
    char tmp[256];
    const char* ptr;
    uint8_t opcode;
    uint8_t encoding;
    uint64_t imm;
    uint8_t reg;
    const mush_op* desc;

    ptr = iptr;
    opcode = *ptr++;
    desc = mush_op_table + opcode;
    strcpy(buffer, desc->mnemo);
    strcat(buffer, " ");

    for (size_t i = 0; i < 2; ++i)
    {
        encoding = desc->encoding[i];
        if (encoding == A_NONE)
            break;
        if (i != 0)
            strcat(buffer, ", ");
        switch (encoding)
        {
        case A_REG:
            reg = *ptr++;
            strcat(buffer, mush_reg_table[reg]);
            break;
        case A_IMM64:
            imm = *(uint64_t*)ptr;
            ptr += 8;
            sprintf(tmp, "0x%016llx", imm);
            strcat(buffer, tmp);
            break;
        case A_IMM32:
            imm = *(uint32_t*)ptr;
            ptr += 4;
            sprintf(tmp, "0x%08llx", imm);
            strcat(buffer, tmp);
            break;
        case A_IMM16:
            imm = *(uint16_t*)ptr;
            ptr += 2;
            sprintf(tmp, "0x%04llx", imm);
            strcat(buffer, tmp);
            break;
        case A_IMM8:
            imm = *(uint8_t*)ptr;
            ptr += 1;
            sprintf(tmp, "0x%02llx", imm);
            strcat(buffer, tmp);
            break;
        }
    }
    return ptr;
}
