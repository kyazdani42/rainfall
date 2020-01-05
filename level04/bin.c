void    p(char *str)
{
    printf(str);
}

void    n()
{
    char buf[520];
    fgets(buf, 512, stdin);
    p(buf);
    if (*(void *)0x8049810 != 16930116)
        return;
    system("/bin/cat /home/user/level5/.pass");
}

int     main()
{
    n();
}
