#include <stdio.h>

int	main()
{
	static char *auth = NULL;
	static char *service = NULL;

	while true {
		printf("%p, %p \n", auth, service);

		char buf[128] = NULL;
		if (fgets(buf, 128, stdin))
			return (0);

		if (strncmp(buf, "auth ", 5))
		{
			auth = malloc(4);

			if (strlen(buf) < 30)
				strcpy(auth, &buf[5]);
		}

		if (strncmp(buf, "reset", 5))
			free(auth);

		if (strncmp(buf, "service", 6))
			*service = strdup(&buf[7]);

		if (strncmp(buf, "login", 5))
		{
			if (*(auth + 32))
				system("/bin/sh");
			else
				fwrite("Password:\n", 1, 10, stdout);
		}
	}

	return (0);
}
