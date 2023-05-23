/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:34:54 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t bytes)
{
	const unsigned char	*it1 = ptr1;
	const unsigned char	*it2 = ptr2;
	size_t				i;

	if (bytes == 0)
		return (0);
	i = 0;
	while (it1[i] == it2[i] && i < bytes)
		i++;
	return (it1[i] - it2[i]);
}
