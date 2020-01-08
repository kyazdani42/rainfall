#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	m()
{
	time_t t = time(NULL);
	printf("%s - %d\n", (char *)0x8049960, t);
}

int	main(int ac, char **av)
{
	char **addr1 = malloc(2 * sizeof(char *));
	addr1[0] = (char *)0x1;
	addr1[1] = (char *)malloc(8);

	char **addr2 = malloc(2 * sizeof(char *));
	addr2[0] = (char *)0x2;
	addr2[1] = (char *)malloc(8);

	strcpy(addr1[1], av[1]);
	strcpy(addr2[1], av[2]);

	FILE *password = fopen("/home/user/level8/.pass", "r");

	// this should point to a location in the heap (like addr2[1])
	// and then we should override the return value to move to the function m
	fgets((char *)0x8049960, 68, password);

	puts("~~");

	return (0);
}
