#include "libft.h"

char	*arr_str[] = {
	"Hatsune",
	"Miku",
	"is",
	"cute",
	NULL
};
char	**end = arr_str + (sizeof(arr_str) / sizeof(arr_str[0]));

void	iteri_strinsertion(unsigned int i, void *p_str)
{
	char	**p_it;

	p_it = p_str;
	while (i-- && ft_strcmp(p_it[i], p_it[i + 1]) > 0)
		ft_memswap(&p_it[i], &p_it[i + 1], sizeof(char *));
}

// static void	insertion_core(void *begin, size_t len, size_t data_size,
// 			t_ftfind ft_swapif)
// {
// 	void			*element;
// 	void			*it_insert;
// 	unsigned int	i;

// 	element = begin + data_size;
// 	i = -1;
// 	while (++i < len)
// 	{
// 		it_insert = element;
// 		while (begin < it_insert
// 			&& ft_swapif(i, it_insert, it_insert - data_size))
// 		{
// 			ft_memswap(it_insert, it_insert - data_size, data_size);
// 			it_insert -= data_size;
// 		}
// 		element += data_size;
// 	}
// }

// void	sort_insertion(void *begin, size_t len, size_t data_size,
// 			t_ftfind ft_swapif)
// {
// 	int	err;

// 	err = 0;
// 	if (begin == NULL)
// 		err = ft_dprintf(2, "ft_sort: NULL begin\n");
// 	if (data_size == 0)
// 		err = ft_dprintf(2, "ft_sort: Invalid data_size: %d\n", data_size);
// 	if (ft_swapif == NULL)
// 		err = ft_dprintf(2, "ft_sort: NULL cmp function\n");
// 	if (err == 0)
// 		insertion_core(begin, len, data_size, ft_swapif);
// }

int	main(void)
{
	for (char **it = arr_str; it < end; it++)
		ft_printf("it: %s\n", *it);
	ft_strlistiteri(arr_str, iteri_strinsertion);
	ft_strlistiteri(arr_str, iteri_strinsertion);
	for (char **it = arr_str; it < end; it++)
		ft_printf("it: %s\n", *it);

}
