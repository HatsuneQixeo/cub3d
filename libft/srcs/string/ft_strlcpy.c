/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 12:20:13 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	const size_t	len_src = ft_strlen(src);

	if (dstsize == 0)
		return (len_src);
	while (*src != '\0' && --dstsize)
		*dst++ = *src++;
	*dst = '\0';
	return (len_src);
}
