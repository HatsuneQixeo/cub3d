/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strskip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:02:31 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

char	*ft_strskip_chr(const char *str, char c)
{
	if (str == NULL)
		return (NULL);
	while (*str != '\0' && *str == c)
		str++;
	return ((char *)str);
}

char	*ft_strskip_is(const char *str, t_ftis ft_is)
{
	if (str == NULL)
		return (NULL);
	else if (ft_is == NULL)
		return ((char *)str);
	while (*str != '\0' && ft_is(*str))
		str++;
	return ((char *)str);
}

char	*ft_strskip_set(const char *str, const char *set)
{
	if (str == NULL)
		return (NULL);
	else if (set == NULL)
		return ((char *)str);
	while (*str != '\0' && ft_strchr(set, *str))
		str++;
	return ((char *)str);
}
