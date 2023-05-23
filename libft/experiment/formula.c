#include "libft.h"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putendl_fd("Bad arguments", 2);
		return (1);
	}
	const double	a = atoi(argv[1]) / 255.0;
	const double	b = atoi(argv[2]) / 255.0;
	const double	c = (1 - a) + (a * (1 - b));

	printf("a: %f\n", a);
	printf("b: %f\n", b);
	printf("c: %f\n", c);
}
