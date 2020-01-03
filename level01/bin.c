#include <stdio.h>
#include <stdlib.h>

int     main(int ac, char **av)
{
    char buf[64];
    gets(buf);
}

void    run() {
    fwrite("Good... Wait what?\n", 13, 1, stdout);
    system("/bin/sh");
}
