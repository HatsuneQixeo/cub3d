/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insertion_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:24:00 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libalgo.h"
#include "ft_printf.h"

static int	errvar(void *begin, size_t data_size, t_ftcmp cmp)
{
	int	err;

	err = 0;
	if (begin == NULL)
		err = ft_dprintf(2, "ft_sort: NULL begin\n");
	if (data_size == 0)
		err = ft_dprintf(2, "ft_sort: Invalid data_size: %d\n", data_size);
	if (cmp == NULL)
		err = ft_dprintf(2, "ft_sort: NULL cmp function\n");
	return (err);
}

void	sort_insertion(void *begin, size_t len, size_t data_size,
			t_ftcmp cmp)
{
	void	*element;
	void	*it_insert;

	if (errvar(begin, data_size, cmp))
		return ;
	element = begin + data_size;
	while (len--)
	{
		it_insert = element;
		while (begin < it_insert
			&& cmp(it_insert - data_size, it_insert) > 0)
		{
			ft_memswap(it_insert - data_size, it_insert, data_size);
			it_insert -= data_size;
		}
		element += data_size;
	}
}
