/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:50:25 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	const size_t	dst_len = ft_strlen(dst);
	const size_t	src_len = ft_strlen(src);

	if (size <= dst_len)
		return (size + src_len);
	dst += dst_len;
	while (*src != '\0' && --size > dst_len)
		*dst++ = *src++;
	*dst = '\0';
	return (src_len + dst_len);
}
