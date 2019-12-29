#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

int     main(int ac, char **av)
{
    if (atoi(av[1]) != 0x1a7) {
      fwrite("No \n", 1, 5, stderr);
    } else {
      const char* shell = "/bin/sh";
      char *argv = strdup(shell);

      gid_t gid = getegid();
      uid_t uid = geteuid();

      setresgid(gid, gid, gid);
      setresuid(uid, uid, uid);

      execv(shell, &argv);
    }

    return (0);
}
