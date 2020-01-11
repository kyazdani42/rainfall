#include <stdlib.h>
#include <string.h>

class N {
	private:
		int value;
		char nstr[108];

	public:
		virtual N operator + (N &n) {
			return (N(value + n.value));
		}

		virtual N operator - (N &n) {
			return (N(value - n.value));
		}

		void	setAnnotation(char *v) {
			memcpy(nstr, v, strlen(v));
		}

		N(int v) {
			value = v;
		}
};

int	main(int ac, char **av)
{
	if (ac < 2)
		exit(1);

	N *ptr = new N(5);
	N *ptr2 = new N(6);

	ptr->setAnnotation(av[1]);

	*ptr2 + *ptr;

	return (0);
}
