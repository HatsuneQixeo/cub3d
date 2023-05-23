/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:02:54 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

void	*ft_memmove(void *dst, const void *src, size_t bytes)
{
	const char	*it_src = src;
	char		*it_dst;

	it_dst = dst;
	if (src == NULL || dst == NULL)
		return (dst);
	if (dst > src)
		while (bytes--)
			it_dst[bytes] = it_src[bytes];
	else if (dst < src)
		while (bytes--)
			*it_dst++ = *it_src++;
	return (dst);
}
