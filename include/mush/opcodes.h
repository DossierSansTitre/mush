#ifndef INCLUDED_MUSH_OPCODES_H
#define INCLUDED_MUSH_OPCODES_H

#define A_NONE  0
#define A_REG   1
#define A_IMM8  2
#define A_IMM16 3
#define A_IMM32 4
#define A_IMM64 5

typedef struct
{
    const char* mnemo;
    uint8_t     encoding[2];
} mush_op;

static const mush_op mush_op_table[] = {
    {"NOP"},
    {"MOV", {A_REG, A_REG}},
    {"MOV", {A_REG, A_IMM64}},
    {"MOV", {A_REG, A_IMM32}},
    {"MOV", {A_REG, A_IMM16}},
    {"MOV", {A_REG, A_IMM8}},
    {"PUSH", {A_REG}},
    {"POP", {A_REG}}
};

#endif
