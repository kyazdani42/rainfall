#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	FILE *pass = fopen("/home/user/end/.pass", "r");
	char buf[136];

	memset(buf, 0, 33);

	if (!pass || ac != 2)
		return 0xffffffff;

	fread(buf, 1, 66, pass);
	buf[64] = 0;

	int t = atoi(av[1]);
	buf[t] = 0;

	fread(&buf[66], 1, 65, pass);

	fclose(pass);

	if (strcmp(buf, av[1]) != 0)
		puts(&buf[66]);
	else
		execl("/bin/sh", "sh", NULL);

	return 0;
}
