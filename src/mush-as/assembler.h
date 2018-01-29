#ifndef INCLUDED_PRIVATE_MUSH_AS_ASSEMBLER_H
#define INCLUDED_PRIVATE_MUSH_AS_ASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <mush/opcodes.h>

typedef enum
{
    tLABEL,
    tIDENTIFIER,
    tREGISTER,
    tCOMMA,
    tNUMBER,
    tEOL,
    tEOF
} token_type;

typedef struct
{
    token_type  type;
    union
    {
        uint64_t    integer;
        char*       str;
    };
} token;

typedef struct
{
    char*   buffer;
    size_t  buffer_size;
    size_t  cursor;
    int     eof;
} lexer;

typedef struct
{
    char*   buffer;
    size_t  size;
    size_t  capacity;
} segment;

typedef struct
{
    segment*    text;
} assembler;

/*
 * init.c
 */
assembler*  assembler_init(void);
void        assembler_quit(assembler* assembler);

/*
 * lexer.c
 */

lexer*  lexer_open(const char* filename);
void    lexer_close(lexer* lex);
token*  lexer_token(lexer* lex);
void    lexer_token_free(token* tok);

/*
 * segment.c
 */

segment*    segment_init();
void        segment_free(segment* seg);
void        segment_append8(segment* seg, uint8_t value);
void        segment_append16(segment* seg, uint16_t value);
void        segment_append32(segment* seg, uint32_t value);
void        segment_append64(segment* seg, uint64_t value);

/*
 * assembler.c
 */
void    assembler_run(assembler* a, const char* filename);
void    assembler_serialize(assembler* as, const char* filename);

#endif
