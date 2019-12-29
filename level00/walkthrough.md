When we enter the vm, we can see a level0 binary with the suid bit:
```shell
$ ls -l level0
-rwsr-x---+ 1 level1 users 747441 Mar  6  2016 level0
```

When we execute this binary without parameter, we get a segmentation fault. Passing a random parameter always prints 'No !\n':
```shell
$ ./level0 random
No !
```

So we started reversing this with gdb: 
- the binary uses atoi on the first argument and then makes a comparison:
```
(gdb) disass main
...
0x08048ed1 <+17>:	mov    DWORD PTR [esp],eax
0x08048ed4 <+20>:	call   0x8049710 <atoi>
0x08048ed9 <+25>:	cmp    eax,0x1a7
...

(gdb) b *0x08048ed4
Breakpoint 1 at 0x8048ed4

(gdb) r 1
Starting program: /home/user/level0/level0 1
Breakpoint 1, 0x08048ed4 in main ()

(gdb) x/wx $esp
0xbffff6f0:	0xbffff8e2

(gdb) x/s 0xbffff8e2
0xbffff8e2:	 "1"
```

- if the value passed in is not 0x1a7 (or 423 in decimal), it will jump to the `fwrite` call outputting the "No !\n" on stderr:
```
(gdb) disass main
...
0x08048ed9 <+25>:	cmp    eax,0x1a7
0x08048ede <+30>:	jne    0x8048f58 <main+152>
...
0x08048f58 <+152>:	mov    eax,ds:0x80ee170
0x08048f5d <+157>:	mov    edx,eax
0x08048f5f <+159>:	mov    eax,0x80c5350
0x08048f64 <+164>:	mov    DWORD PTR [esp+0xc],edx
0x08048f68 <+168>:	mov    DWORD PTR [esp+0x8],0x5
0x08048f70 <+176>:	mov    DWORD PTR [esp+0x4],0x1
0x08048f78 <+184>:	mov    DWORD PTR [esp],eax
0x08048f7b <+187>:	call   0x804a230 <fwrite>
...

(gdb) b *0x08048f7b
Breakpoint 2 at 0x8048f7b

(gdb) c
Continuing.

(gdb) x/4wx $esp
0xbffff6f0:	0x080c5350	0x00000001	0x00000005	0x080ee7a0

(gdb) x/s 0x80c5350
0x80c5350:	 "No !\n
```

- if the value is 0x1a7, it sets the uid/gid of the owner and calls /bin/sh with thoses permissions:
```
(gdb) disas
...
0x08048ee0 <+32>:	mov    DWORD PTR [esp],0x80c5348
0x08048ee7 <+39>:	call   0x8050bf0 <strdup>
0x08048eec <+44>:	mov    DWORD PTR [esp+0x10],eax
0x08048ef0 <+48>:	mov    DWORD PTR [esp+0x14],0x0
0x08048ef8 <+56>:	call   0x8054680 <getegid>
0x08048efd <+61>:	mov    DWORD PTR [esp+0x1c],eax
0x08048f01 <+65>:	call   0x8054670 <geteuid>
0x08048f06 <+70>:	mov    DWORD PTR [esp+0x18],eax
0x08048f0a <+74>:	mov    eax,DWORD PTR [esp+0x1c]
0x08048f0e <+78>:	mov    DWORD PTR [esp+0x8],eax
0x08048f12 <+82>:	mov    eax,DWORD PTR [esp+0x1c]
0x08048f16 <+86>:	mov    DWORD PTR [esp+0x4],eax
0x08048f1a <+90>:	mov    eax,DWORD PTR [esp+0x1c]
0x08048f1e <+94>:	mov    DWORD PTR [esp],eax
0x08048f21 <+97>:	call   0x8054700 <setresgid>
0x08048f26 <+102>:	mov    eax,DWORD PTR [esp+0x18]
0x08048f2a <+106>:	mov    DWORD PTR [esp+0x8],eax
0x08048f2e <+110>:	mov    eax,DWORD PTR [esp+0x18]
0x08048f32 <+114>:	mov    DWORD PTR [esp+0x4],eax
0x08048f36 <+118>:	mov    eax,DWORD PTR [esp+0x18]
0x08048f3a <+122>:	mov    DWORD PTR [esp],eax
0x08048f3d <+125>:	call   0x8054690 <setresuid>
0x08048f42 <+130>:	lea    eax,[esp+0x10]
0x08048f46 <+134>:	mov    DWORD PTR [esp+0x4],eax
0x08048f4a <+138>:	mov    DWORD PTR [esp],0x80c5348
0x08048f51 <+145>:	call   0x8054640 <execv>
...

(gdb) b *0x08048f51
Breakpoint 1 at 0x8048f51

(gdb) r 423
Starting program: /home/user/level0/level0 423
Breakpoint 1, 0x08048f51 in main ()

(gdb) x/2wx $esp
0xbffff6f0:	0x080c5348	0xbffff700

(gdb) x/s 0x80c5348
0x80c5348:	 "/bin/sh" -> execv execution

(gdb) x/wx 0xbffff700
0xbffff700:	0x080f2718 -> is a pointer to the string (execv argv parameter)
(gdb) x/s 0x80f2718
0x80f2718:	 "/bin/sh"
```

- As `/bin/sh` is a symlink to `/bin/dash`, and dash is painful to use, we decide to launch bash to move around more freely, go the `/home/user/level1` folder and get the flag for the next level:
```shell
level0$ ./level0 423
$ HOME=/home/user/level1 bash
...

level1$ cat .pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
```
