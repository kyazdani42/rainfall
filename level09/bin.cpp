class N {
	public:
		virtual operator+() {}
		virtual operator-() {}
		static int N(void *ptr, int param) {
		}
}

int	main(int ac, char **av)
{
	if (ac < 2)
		exit(1);

	int *v = new 108;
	N::N(v, 5);

}
