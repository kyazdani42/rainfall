#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void    p()
{
    fflush(stdout);

    char buf[76];
    gets(buf);

    // this is not perfect i think
    buf[63] = *(buf - 0x4);

    if ((buf[63] & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", &buf[63]);
        exit(1);
    }
    puts(buf);
    strdup(buf);
}

int     main()
{
    p();
}

