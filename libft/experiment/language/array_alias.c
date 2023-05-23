#include "libft.h"

typedef struct s_test
{
	char	*name;
	int		age;
}		t_test;

typedef const t_test	t_testarr[];
typedef const char		*t_sstring[];

/* Nope, doesn't work like that */
// void	guess_size(const t_sstring p_array)
// {
// 	ft_printf("Size: %ld\n", sizeof(p_array) / sizeof(p_array[0]));
// }

int	main(void)
{
	const t_sstring	array = {
		"string1",
		"string2",
		NULL
	};
	const t_testarr	teat = {
	{"Hatsune Miku", 16},
	};

	ft_printf("Size: %ld\n", sizeof(array) / sizeof(array[0]));
	for (int i = 0; i < (int)(sizeof(teat) / sizeof(teat[0])); i++)
	{
		ft_printf("Name : %s\nAge: %d\n", teat[i].name, teat[i].age);
	}
	guess_size(array);
	ft_strlistiteri((char **)array, iteristr_showstr);
}
