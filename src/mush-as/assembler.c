#include <assembler.h>

static int lookup_opcode(uint8_t* dst, const char* mnemo, const uint8_t* enc)
{
    size_t count;
    const mush_op* desc;

    count = sizeof(mush_op_table) / sizeof(*mush_op_table);
    for (uint8_t op = 0; op < count; ++op)
    {
        desc = mush_op_table + op;
        if (strcmp(desc->mnemo, mnemo))
            continue;
        if (desc->encoding[0] != enc[0])
            continue;
        if (desc->encoding[1] != enc[1])
            continue;
        *dst = op;
        return 1;
    }
    return 0;
}

void assembler_run(assembler* a, const char* filename)
{
    lexer* l;
    token* tok;
    char* mnemo;
    uint8_t op;
    uint8_t enc[2];
    uint64_t imm;
    uint8_t reg[2];
    size_t arg_count;
    size_t reg_count;

    l = lexer_open(filename);
    for (;;)
    {
        tok = lexer_token(l);
        if (tok == NULL)
            break;
        if (tok->type == tLABEL || tok->type == tEOL || tok->type == tEOF)
        {
            lexer_token_free(tok);
            continue;
        }
        mnemo = strdup(tok->str);
        lexer_token_free(tok);
        arg_count = 0;
        reg_count = 0;
        enc[0] = A_NONE;
        enc[1] = A_NONE;

        for (;;)
        {
            tok = lexer_token(l);
            if (tok->type == tEOL)
            {
                lexer_token_free(tok);
                break;
            }
            if (tok->type == tCOMMA)
            {
                lexer_token_free(tok);
            }
            else
            {
                if (tok->type == tREGISTER)
                {
                    reg[reg_count++] = tok->integer;
                    enc[arg_count] = A_REG;
                }
                else if (tok->type == tNUMBER)
                {
                    imm = tok->integer;
                    enc[arg_count] = A_IMM64;
                }
                arg_count++;
                lexer_token_free(tok);
            }
        }

        if (lookup_opcode(&op, mnemo, enc))
        {
            segment_append8(a->text, op);
            for (size_t i = 0; i < 2; ++i)
            {
                if (enc[i] == A_NONE)
                    break;
                switch (enc[i])
                {
                case A_REG:
                    segment_append8(a->text, reg[i]);
                    break;
                case A_IMM8:
                    segment_append8(a->text, imm);
                    break;
                case A_IMM16:
                    segment_append16(a->text, imm);
                    break;
                case A_IMM32:
                    segment_append32(a->text, imm);
                    break;
                case A_IMM64:
                    segment_append64(a->text, imm);
                    break;
                }
            }
        }
        else
            printf("Unrecognized: %s\n", mnemo);
        free(mnemo);
    }
    lexer_close(l);
}

void assembler_serialize(assembler* as, const char* filename)
{
    FILE* f;
    uint32_t seg_base;
    segment* segtbl;
    segment* header;

    f = fopen(filename, "w");

    segtbl = segment_init();
    header = segment_init();

    /* Semi-hardcoded segment table */
    seg_base = 0x30 * 2;
    segment_append32(segtbl, 1);
    segment_append32(segtbl, seg_base);
    segment_append32(segtbl, as->text->size);
    segment_append32(segtbl, as->text->size);
    segment_append32(segtbl, 0);
    segment_append32(segtbl, 0);
    segment_append32(segtbl, 0);
    segment_append32(segtbl, 0);
    segment_append32(segtbl, 0);
    segment_append32(segtbl, 0);
    segment_append32(segtbl, 0);
    segment_append32(segtbl, 0);

    /* Header */
    segment_append8(header, 'M');
    segment_append8(header, 'U');
    segment_append8(header, 'S');
    segment_append8(header, 'H');
    segment_append32(header, 0x00010000);
    segment_append32(header, 0x00010000);
    segment_append32(header, 0);
    segment_append32(header, 0);
    segment_append32(header, 0);
    segment_append32(header, 0);
    segment_append32(header, 0);
    segment_append32(header, 0);
    segment_append32(header, 0x30);
    segment_append32(header, 0x30);
    segment_append32(header, 1);

    fwrite(header->buffer, header->size, 1, f);
    fwrite(segtbl->buffer, segtbl->size, 1, f);
    fwrite(as->text->buffer, as->text->size, 1, f);

    segment_free(header);
    segment_free(segtbl);
    fclose(f);
}
