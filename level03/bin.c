#include <stdio.h>
#include <stdlib.h>

void    v()
{
    char buf[520];
    fgets(buf, 512, stdin);
    printf(buf);

    if (*(unsigned char *)0x0804988c != 64)
        return;

    fwrite("Wait what?!\n", 1, 12, stdout);
    system("/bin/sh");
}

int     main()
{
    v();
}
