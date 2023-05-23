/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:15:34 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_swapbyte(void *p_a, void *p_b)
{
	char *const	a = p_a;
	char *const	b = p_b;
	const char	tmp = *a;

	*a = *b;
	*b = tmp;
}

void	ft_memswap(void *ptr1, void *ptr2, size_t bytes)
{
	while (bytes--)
		ft_swapbyte(ptr1++, ptr2++);
}
