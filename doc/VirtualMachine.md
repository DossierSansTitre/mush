# The MUSH virtual machine

MUSH is a 64 bits virtual machine.

## Registers

## General purpose

| name | code |
| r0   | 0x00 |
| r1   | 0x01 |
| r2   | 0x02 |
| r3   | 0x03 |
| r4   | 0x04 |
| r5   | 0x05 |
| r6   | 0x06 |
| r7   | 0x07 |
| r8   | 0x08 |
| r9   | 0x09 |
| r10  | 0x0a |
| r11  | 0x0b |
| r12  | 0x0c |
| r13  | 0x0d |
| rsp  | 0x0e |
| rbp  | 0x0f |

## Specific

| name   | code | desc                    |
| rip    | 0xf0 | The instruction pointer |
| rflags | 0xf1 | The flags               |

## ABI

`r0` and `r1` are used as return values.
`r2` to `r7` (included) are the function parameters.
`r8` and `r9` are additionnal temporary registers.
`r10` to `r13` (incldued) must be preserved across function calls.

## Register encoding

`r` denote a 4 bit register code, encoding only the general purpose registers.
`rx` denote a 8 bit "extended" register code.

When encoding an instruction using 2 or more simple registers, they are packed. The first register takes the least significant bytes.
