#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	n()
{
	system("/bin/cat /home/user/level7/.pass");
}

void	m(void)
{
	puts("Nope.\n");
}

int	main(int ac, char **av)
{
	char *buf = (char *)malloc(64);

	void  (*func)(void) = malloc(4);
	func = &m;

	strcpy(buf, av[1]);

	(*func)();
}

