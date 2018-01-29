#include <assembler.h>

lexer* lexer_open(const char* filename)
{
    lexer* lex;
    FILE* file;

    lex = malloc(sizeof(lexer));

    file = fopen(filename, "r");
    fseek(file, 0, SEEK_END);
    lex->buffer_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    lex->buffer = malloc(lex->buffer_size);
    fread(lex->buffer, lex->buffer_size, 1, file);
    fclose(file);

    lex->cursor = 0;
    lex->eof = 0;
    return lex;
}

void lexer_close(lexer* lex)
{
    free(lex->buffer);
    free(lex);
}

token* lexer_token(lexer* lex)
{
    char tmp[256];
    size_t tmp_size;
    int is_reg;
    token* tok;
    char c;

    if (lex->eof)
        return NULL;

    /* Skip whitespace */
    while (lex->cursor < lex->buffer_size)
    {
        c = lex->buffer[lex->cursor];
        if (c == ' ' || c == '\t' || c == '\f' || c == '\v')
            lex->cursor++;
        else
            break;
    }

    tok = malloc(sizeof(token));

    if (lex->cursor >= lex->buffer_size)
    {
        lex->eof = 1;
        tok->type = tEOF;
    }
    else
    {
        c = lex->buffer[lex->cursor];

        if (c == '\n')
        {
            tok->type = tEOL;
            lex->cursor++;
        }
        else if (c == ',')
        {
            tok->type = tCOMMA;
            lex->cursor++;
        }
        else
        {
            tmp_size = 0;
            for (;;)
            {
                c = lex->buffer[lex->cursor];
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
                {
                    tmp[tmp_size++] = c;
                    lex->cursor++;
                }
                else
                    break;
            }
            tmp[tmp_size] = 0;
            is_reg = 0;
            if (tmp[0] == 'r' && tmp[1] != 0)
            {
                is_reg = 1;
                for (size_t i = 1; i < tmp_size; ++i)
                {
                    if (tmp[i] < '0' || tmp[i] > '9')
                    {
                        is_reg = 0;
                        break;
                    }
                }
            }
            if (is_reg)
            {
                tok->type = tREGISTER;
                tok->integer = atoi(tmp + 1);
            }
            else if (strcmp(tmp, "rsp") == 0)
            {
                tok->type = tREGISTER;
                tok->integer = 254;
            }
            else if (strcmp(tmp, "rbp") == 0)
            {
                tok->type = tREGISTER;
                tok->integer = 255;
            }
            else if (c == ':')
            {
                lex->cursor++;
                tok->type = tLABEL;
                tok->str = strdup(tmp);
            }
            else if (tmp[0] == '+' || tmp[0] == '-' || (tmp[0] >= '0' && tmp[0] <= '9'))
            {
                tok->type = tNUMBER;
                tok->integer = strtoul(tmp, NULL, 16);
            }
            else
            {
                tok->type = tIDENTIFIER;
                tok->str = strdup(tmp);
            }
        }
    }
    return tok;
}

void lexer_token_free(token* tok)
{
    if (tok->type == tIDENTIFIER || tok->type == tLABEL)
        free(tok->str);
    free(tok);
}
