/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:02:47 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

void	*ft_memcpy(void *dst, const void *src, size_t bytes)
{
	const char	*it_src = src;
	char		*it_dst;

	it_dst = dst;
	if (src == NULL || dst == NULL)
		return (dst);
	while (bytes--)
		*it_dst++ = *it_src++;
	return (dst);
}
