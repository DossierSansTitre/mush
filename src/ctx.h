#ifndef MUSH_PRIVATE_CTX_H
#define MUSH_PRIVATE_CTX_H

#include <stdint.h>
#include <mush/mush.h>

struct mush_vm_regs
{
    union
    {
        uint64_t        r[16];
        struct
        {
            uint64_t    r0;
            uint64_t    r1;
            uint64_t    r2;
            uint64_t    r3;
            uint64_t    r4;
            uint64_t    r5;
            uint64_t    r6;
            uint64_t    r7;
            uint64_t    r8;
            uint64_t    r9;
            uint64_t    r10;
            uint64_t    r11;
            uint64_t    r12;
            uint64_t    r13;
            uint64_t    rsp;
            uint64_t    rbp;
        };
    };
    uint64_t    rip;
    uint64_t    rflags;
};

struct mush_ctx_
{
    char*               memory;
    size_t              memory_size;
    size_t              memory_capacity;
    struct mush_vm_regs regs;
};

#endif
