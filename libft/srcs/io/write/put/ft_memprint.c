/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:16:42 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

// ft_printf("is: %.*s\n", bpl, ptr_uc);
static void	memprint_loop(const void **ptr, size_t bpl, int pad, size_t i)
{
	const unsigned char	*ptr_uc = *ptr;

	if (bpl == 0)
		return ;
	ft_printf("ptr[%*d]:", pad, i);
	while (bpl--)
		ft_printf(" {%3d}", *ptr_uc++);
	*ptr = ptr_uc;
	ft_printf("\n");
}

void	ft_memprint(const void *ptr, size_t bytes, size_t data_size)
{
	const int	pad = ft_nbrsize(bytes);
	size_t		i;

	if (data_size == 0 || ptr == NULL)
		return ;
	i = 0;
	while (bytes >= data_size)
	{
		memprint_loop(&ptr, data_size, pad, i++);
		bytes -= data_size;
	}
	memprint_loop(&ptr, bytes, pad, i);
}
