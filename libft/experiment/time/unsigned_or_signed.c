#include "exlib.h"
#include <limits.h>

// #define limit	UINT_MAX
// #define limit	INT_MAX
#define limit	100

/**
 * Casting a signed integer to unsigned,
 * and check whether it's inbound should be faster and more concise
 * doesn't seems like casting will degrade in performance either.
 *
 * Not applicable to floating point data, unfortunately
 */

void	*test_casting(void *ptr)
{
	for (long i = 0; i < limit; i++)
		(void)((unsigned long)i > LONG_MAX);
	return (ptr);
}

void	*test_nothing(void *ptr)
{
	for (long i = 0; i < limit; i++)
		(void)(i > LONG_MAX);
	return (ptr);
}

void	*test_unsigned(void *ptr)
{
	for (unsigned long i = 0; i < limit; i++)
		(void)(i > LONG_MAX);
	return (ptr);
}

void	*test_compare(void *ptr)
{
	for (long i = 0; i < limit; i++)
		(void)(i < 0 || i > LONG_MAX);
	return (ptr);
}

int	main(void)
{
	time_debug("casting", test_casting, NULL);
	time_debug("nothing", test_nothing, NULL);
	time_debug("unsigned", test_unsigned, NULL);
	time_debug("compare", test_compare, NULL);
}
