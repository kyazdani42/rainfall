int language = 0;

void	greetuser(char *str)
{
	char buf[72];
	if (language == 1)
		buf = "Hyvää päivää ";
	if (language == 2)
		buf = "Goedemiddag! ";
	if (language == 0)
		buf = "Hello ";

	strcat(buf, str);
	puts(buf);
}

int	main(int ac, char **av)
{
	char buf[80];

	if (ac < 3)
		return 1;

	memset(buf, 0, 19);

	strncpy(buf, av[1], 40);
	strncpy(&buf[40], av[2], 32);

	char *lang = getenv("LANG");

	if (lang) {
		if (memcmp(lang, "fi", 2))
			language = 1;
		if (memcmp(lang, "nl", 2))
			language = 2;
	}

	greetuser(buf)

	return;
}
