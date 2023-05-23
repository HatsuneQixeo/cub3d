/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:32:24 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

void	*ft_memchr(const void *ptr, int c, size_t bytes)
{
	const char	*str = ptr;

	c = (char)c;
	while (bytes--)
	{
		if (*str == c)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
