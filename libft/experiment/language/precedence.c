#include "libft.h"

int	ft_test_precendece(int *n)
{
	*n = 39;
	return (831);
}

int	main(void)
{
	int	n;

	n = 831;
	printf("n: %d, pre: %d, n: %d", n, ft_test_precendece(&n), n);
}
