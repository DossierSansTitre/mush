#ifndef MUSH_PRIVATE_CTX_H
#define MUSH_PRIVATE_CTX_H

#include <stddef.h>
#include <stdint.h>
#include <mush/mush.h>

struct mush_vm_regs
{
    union
    {
        uint64_t        r[256];
        struct
        {
            uint64_t    _unused[254];
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
