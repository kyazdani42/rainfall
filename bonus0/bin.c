#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void	p(char *buf, char *str)
{
	char read_buffer[4096];

	puts(str);
	read(0, read_buffer, 4096);
	strchr(read_buffer, '\n');
	strncpy(buf, read_buffer, 20);
}

void	pp(char *buf)
{
	// i think buf1 must override buf2
	// and write something on buf2
	// as something is messing with the
	// stack after that. We might be able
	// to execute a shellcode by erasing the rip value.
	char buf1[20];
	char buf2[20];

	p(buf1, " - ");
	p(buf2, " - ");
	strcpy(buf, buf1);
	// weird stuff happening here
	strcat(buf, buf2);
}

int	main(int ac, char **av)
{
	char buf[42];

	pp(buf);
	puts(buf);
	return (0);
}
