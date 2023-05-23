/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_str_ft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:52:42 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:48 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

int	cmp_str(const void *str1, const void *str2)
{
	return (ft_strcmp(str1, str2));
}

int	cmp_strreverse(const void *str1, const void *str2)
{
	return (ft_strcmp(str2, str1));
}

int	cmp_strprefix(const void *str, const void *prefix)
{
	const char	*it_str = str;
	const char	*it_prefix = prefix;
	size_t		i;

	i = 0;
	if (str == NULL || prefix == NULL)
		return (0);
	while (it_str[i] == it_prefix[i] && it_str[i] != '\0')
		i++;
	if (it_prefix[i] == '\0')
		return (0);
	return (it_str[i] - it_prefix[i]);
}

int	cmp_strsuffix(const void *str, const void *suffix)
{
	const char	*it_str = ft_strchr(str--, '\0');
	const char	*it_suffix = ft_strchr(suffix--, '\0');

	while ((--it_str != str) + (--it_suffix != suffix) == 2)
	{
		if (*it_str != *it_suffix)
			return (*it_str - *it_suffix);
	}
	if (it_suffix + 1 == suffix)
		return (0);
	return (-*it_suffix);
}

int	cmp_strlen(const void *str1, const void *str2)
{
	return (ft_strlen(str1) - ft_strlen(str2));
}
