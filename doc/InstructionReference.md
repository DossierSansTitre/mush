# The MUSH instruction set

Notes: The encoding order is fixed, it is always:

 * Opcode
 * Registers
 * Indirect
 * Relative
 * Immediate

Relative is indirect with RIP base.

## NOP

Opcodes:

| opcode | encoding |
| 0x00   | N/A      |

Do nothing.

## MOV

| opcode | encoding   |
| 0x01   | r/r        |
| 0x02   | rx/rx      |
| 0x03   | rx/imm64   |
| 0x04   | rx/imm32   |
| 0x05   | rx/imm16   |
| 0x06   | rx/imm8    |
| 0x07   | rx/
