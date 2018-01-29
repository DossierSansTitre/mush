# The Mush Bytecode file format

Mush uses a custom file format for its bytecode, not unlike ELF or similar
machine code object files.

Each file contains:

 * A symbol table
 * One or more segments

Each segment has some flags, and can contain relocations.
There are two types of relocations:

 * Symbol relocations, used to perform symbolic lookup at dynalic link time.
 * X-segment relocations, ususally used to create references to data from code.

This architecture is extremely flexible, and the additionnal conplexity it creates
is moderate.

All multi-byte components are stored in little-endian.

## Header

At the very start of the file is the mush header.

| offset  | size | name          | desc                                               |
| 0x00    | 0x4  | magic         | The mush magic, should be "MUSH"                   |
| 0x04    | 0x4  | mush_version  | The version of mush that authored this file        |
| 0x08    | 0x4  | abi_version   | The mush ABI version this file is compatible with  |
| 0x0c    | 0x4  | flags         | Reserved                                           |
| 0x10    | 0x4  | symstr_base   | The base offset in the file for the symbol strings |
| 0x14    | 0x4  | symstr_size   | The size in bytes of the symbol strings            |
| 0x18    | 0x4  | symtbl_base   | The base offset in the file for the symbol table   |
| 0x1c    | 0x4  | symtbl_size   | The size in bytes of the symbol table              |
| 0x20    | 0x4  | sym_count     | The number of symbols in the sym table             |
| 0x24    | 0x4  | segtbl_base   | The base offset in the file for the segment table  |
| 0x28    | 0x4  | segtbl_size   | The size in bytes of the segment table             |
| 0x2c    | 0x4  | seg_count     | The number of segments in the file                 |

## The symbol string blob

Referenced as `symstr` in the header, this is simply a blob of NUL-terminated
ascii strings. Symbols should be composed of alphanumeric characters, as well as `-` and `_` only.
Symbols cannot start with `-` or a number. Symbols starting with `_`, or containing two underscores
in a row, are reserved by the implementation. Symbol length SHOULD BE at least 1 and no more than
255 in bytes.

## The symbol table

Referenced as `symtbl`, this simply store offsets to the symbols defined in `symstr`.
This table is simply a flat array of `sym_count` 4 bytes offsets, referencing the `symstr`
table. Comforming authoring applications shall make each entry in this table point to
an unique string in `symstr`. Conforming authoring implementations shall leave no entry in
symstr unused. Conforming authoring implementations shall sort these offsets in ascending order.

## The segment table

Referenced as `segtbl`, this is a flat array of the following structure:

| offset | size | name         | desc                                |
| 0x00   | 0x04 | flags        | See below                           |
| 0x04   | 0x04 | seg_base     | The segment base                    |
| 0x08   | 0x04 | seg_filesize | The segment size in the file        |
| 0x0c   | 0x04 | seg_memsize  | The segment size in memory          |
| 0x10   | 0x04 | relsym_base  | The symbol relocation table offset  |
| 0x14   | 0x04 | relsym_size  | The symbol relocation table size    |
| 0x18   | 0x04 | relsym_count | The symbol relocation count         |
| 0x1c   | 0x04 | relseg_base  | The segment relocation table offset |
| 0x20   | 0x04 | relseg_size  | The segment relocation table size   |
| 0x24   | 0x04 | relseg_count | The segment relocation count        |
| 0x28   | 0x08 | unused       | Set to zero                         |

Flags are combined from the following:

| name              | value | desc                        |
| MUSH_VM_SEG_EXEC  | 0x01  | The segment can be executed |
| MUSH_VM_SEG_WRITE | 0x02  | The segment can be written  |

## The symbol relocation table

The symbol relocation table is simply a flat array of 4 bytes integer.
Each integer denotes an offset in the corresponding segment where the relocation
takes place.

The relocations are performed as follows:

 * The dynamic symbol relocator looks up the 4 bytes value at the given offset.
 * The value is used as an offset in `symtbl`.
 * The systbl values is used as an index to fetch the symbol name in `symstr`.
 * The virtual machine fetch the symbol ID for the given symbol name.
 * The symbol ID is patched back at the offset in memory.

## The segment relocation table

The symbol relocation table is a flat array of the following:

| offset | size | name | desc                       |
| 0x00   | 0x04 | seg  | The destination segment ID |

TODO: Finish this

## Alignment considerations

The header, `symstr`, `symtbl`, `segtbl`, the segments, the `relsyms` and the `relsegs`
SHOULD BE aligned to 64 bytes within the file. For the header, this constraint is always
fulfilled, as its offset is always zero, but care should be taken about the other
sections.

The file size SHOULD be a multiple of 64.

When padding bytes are to be added, they SHOULD have the value `0xff`.

Authoring softwares are not expected to emit the sections in any particular order,
nor are they expected to order the sections so as to minimize padding bytes.
