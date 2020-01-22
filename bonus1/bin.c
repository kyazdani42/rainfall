#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int	t;
	char	buf[40];

	t = atoi(av[1]);
	if (t > 9) {
		return 1;
	}

	memcpy(buf, av[2], t * 4);

	if (t == 0x574f4c46) {
		execl("/bin/sh", "sh", NULL);
	}

	return 0;
}
