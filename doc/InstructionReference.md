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
| 0x02   | r/imm64    |
| 0x03   | r/imm32    |
| 0x04   | r/imm16    |
| 0x05   | r/imm8     |
