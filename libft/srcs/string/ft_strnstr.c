/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:35:35 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	const size_t	len_to_find = ft_strlen(to_find);

	if (len_to_find == 0)
		return ((char *)str);
	str--;
	while (*++str != '\0' && len-- >= len_to_find)
		if (!ft_strncmp(str, to_find, len_to_find))
			return ((char *)str);
	return (NULL);
}
