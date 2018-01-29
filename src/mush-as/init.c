#include <assembler.h>

assembler* assembler_init()
{
    assembler* a;

    a = malloc(sizeof(assembler));
    a->text = segment_init();
    return a;
}

void assembler_quit(assembler* a)
{
    segment_free(a->text);
    free(a);
}
