#include "libft.h"

/**
 * @brief Different approach for calculating the amount of pixels
 * the given image size will cover (only for width or height)
 * 
 * 
 * 1st) Math:
 * 		Can't believe how wonderful math is
 * 		Pros:
 * 			The fastest, the most compact
 * 		Cons:
 * 			Maybe takes a bit of time to digest?
 * 
 * 2nd) Iterative
 * 		The standard approach
 * 		Pros:
 * 			Looks just how it should, straight foward
 * 		Cons:
 * 			Redundant in a way
 * 
 * 3rd) Recursive
 * 		Worst for a few reason
 * 		Pros:
 * 			??? There's really no reason to use recursive approach
 * 				for such simple calculation
 * 		Cons:
 * 			Highest Memory usage
 * 			Slowest (function overhead from calling itself multiple times)
 * 			Stack overflow if the given value is too large (say a long value)
 * 	
 * @bug Not entirely sure how to treat negative integers,
 * 	but wasn't quite impactful for the project eitherway
 */

#define PIXEL 48

size_t	ft_size_invert_itr(int size)
{
	size_t	tile;

	tile = 1;
	while (size > PIXEL)
	{
		size -= PIXEL;
		tile++;
	}
	return (tile);
}

size_t	ft_size_centered_itr(int size)
{
	size_t	tile;

	tile = 1;
	while (size > PIXEL)
	{
		size -= (PIXEL * 2);
		tile += 2;
	}
	return (tile);
}

size_t	ft_size_invert(int size)
{
	if (size > PIXEL)
		return (1 + ft_size_invert(size - PIXEL));
	return (1);
}

size_t	ft_size_centered(int size)
{
	if (size > PIXEL)
		return (2 + ft_size_centered(size - (PIXEL * 2)));
	return (1);
}

size_t	ft_size_invert_math(size_t size)
{
	return (size / PIXEL + (size % PIXEL != 0));
}

size_t	ft_size_centered_math(size_t size)
{
	if (size == 0)
		return (0);
	return (1 + (size / (PIXEL * 2) + (size % (PIXEL * 2) > PIXEL)) * 2);
}

static void	compare(long nbr)
{
	ft_printf("\nNBR: (%d)", nbr);
	ft_printf("\nInvert\n");
	ft_printf("	recurive:	%d\n", ft_size_invert(nbr));
	ft_printf("	iterative:	%d\n", ft_size_invert_itr(nbr));
	ft_printf("	math:		%d\n", ft_size_invert_math(nbr));
	ft_printf("\nCentered\n");
	ft_printf("	recurive:	%d\n", ft_size_centered(nbr));
	ft_printf("	iterative:	%d\n", ft_size_centered_itr(nbr));
	ft_printf("	math:		%d\n", ft_size_centered_math(nbr));
}

int	main(void)
{
	// compare(2147483648);
	// compare(110592);
	compare(1000000);
	// compare(402000);
	// compare(48);
	// compare(49);
	// compare(96);
	// compare(97);
	// compare(144);
	// compare(145);
}
