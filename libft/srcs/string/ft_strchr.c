/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:35:16 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

char	*ft_strchr(const char *str, int c)
{
	c = (char)c;
	while (*str != '\0' && *str != c)
		str++;
	if (*str == c)
		return ((char *)str);
	return (NULL);
}

char	*ft_strchr_is(const char *str, t_ftis ft_is)
{
	if (!ft_is)
		return (NULL);
	while (*str != '\0')
	{
		if (ft_is(*str))
			return ((char *)str);
		str++;
	}
	return (NULL);
}
