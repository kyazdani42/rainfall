#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void	p(char *buf, char *str)
{
	char read_buffer[4104];

	puts(str);
	read(0, read_buffer, 4096);
	char *ret = strchr(read_buffer, '\n');
	*ret = 0;
	strncpy(buf, read_buffer, 20);
}

void	pp(char *buf)
{
	char buf2[20];
	char buf1[20];

	p(buf1, " - ");
	p(buf2, " - ");
	strcpy(buf, buf1);
	int len = strlen(buf);
	buf[len] = ' ';
	strcat(buf, buf2);
}

int	main(int ac, char **av)
{
	char buf[42];

	pp(buf);
	puts(buf);
	return (0);
}
