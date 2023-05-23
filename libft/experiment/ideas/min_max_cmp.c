#include "libft.h"

void	*ft_max_cmp(const void *a, const void *b, t_ftcmp cmp)
{
	if (cmp(a, b) > 0)
		return ((void *)a);
	else
		return ((void *)b);
}

void	*ft_min_cmp(const void *a, const void *b, t_ftcmp cmp)
{
	if (cmp(a, b) < 0)
		return ((void *)a);
	else
		return ((void *)b);
}
