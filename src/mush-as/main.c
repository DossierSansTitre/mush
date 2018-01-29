#include <assembler.h>

int main(int argc, char** argv)
{
    assembler* as;

    as = assembler_init();

    for (size_t i = 1; i < argc; ++i)
        assembler_run(as, argv[i]);
    assembler_serialize(as, "a.out");
    assembler_quit(as);
    return 0;
}
