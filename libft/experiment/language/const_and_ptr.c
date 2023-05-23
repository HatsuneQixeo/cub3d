#include "libft.h"

void	constptr_and_ptrtoconst(void)
{
	char	add;
	char const	*ptr_to_const;
	const char	*ptr_to_const1;
	char *const	constptr = &add; 
	// *const char	constptr1;

	ptr_to_const = &add;
	ptr_to_const1 = &add;
	// constptr1 = &add;
	add = 'a';
	// Legal
	{
		ptr_to_const++;
		ptr_to_const1++;
		*constptr = 'a';
	}
	// Illegal
	{
		// constptr = &add;
		// *ptr_to_const = 'a';
		// *ptr_to_const1 = 'a';
		// constptr++;
	}
	// constptr1++;
}

// int	main(void)
// {
// 	char	*str;
// 	// Pointer to a constant pointer
// 	// char *const	*ptr;
// 	// Pointer to a constant address
// 	const char	**ptr;

// 	str = "Hatsune Miku";
// 	ptr = &str;
// 	// (*ptr)++;
// 	// *ptr = "Miku";
// 	// **ptr = 'a';
// }

/* Ok */
void	ptrcptr(void *const *ptr)
{
	(void)ptr;
}

/* Ok */
void	ptrptr(void **ptr)
{
	(void)ptr;
}

/* Not ok */
void	cptrptr(const void **ptr)
{
	(void)ptr;
}

/* Not ok */
void	cptrcptr(const void *const *ptr)
{
	(void)ptr;
}

int	main(void)
{
	void	*p;
	void	**pp;

	p = "Hatsune Miku";
	pp = &p;
	ptrcptr(pp);
	ptrptr(pp);
	cptrptr(pp);
	cptrcptr(pp);
}
