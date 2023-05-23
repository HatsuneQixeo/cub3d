#include "libft.h"

/**
 * @brief Feels good to fuck with norminette, but don't do this, for real
 * 
 * @return int*
 */

int	*ft_int(void)
{
	static int	ptr[1];

	return (ptr); 
}

int	main(void)
{
	int	*ptr = ft_int();

	*ptr = 39;
	ft_printf("%d\n", *ft_int());
	*ptr = 831;
	ft_printf("%d\n", *ft_int());
}
