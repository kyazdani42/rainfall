void    p(char *str)
{
    printf(str);
}

void    n()
{
    char buf[520];
    fgets(buf, 512, stdin);
    p(buf);
    if (*(unsigned int *)0x08049810 != 16930116)
        return;
    system("/bin/cat /home/user/level5/.pass");
}

int     main()
{
    n();
}
