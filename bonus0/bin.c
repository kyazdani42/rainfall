#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>

int	p(char *buf, char *str)
{
	char read_buffer[4096];

	puts(str);
	read(0, read_buffer, 4096);
	strchr(read_buffer, '\n');
	strncpy(buf, read_buffer, 20);
}

int	pp(char *buf1)
{
	char buf2[48];

	p(buf2, " - ");
	p(&buf2[17], " - ");
	strcpy(buf1, buf2);
	strcat(buf1, &buf2[17]);
}

int	main(int ac, char **av)
{
	char buf[42];

	puts(pp(buf));
	return (0);
}
