/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:57:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

char	*ft_strtrim(const char *src, const char *set)
{
	char	*end;

	if (src == NULL)
		return (NULL);
	else if (set == NULL)
		return (ft_strdup(src));
	end = ft_strchr(src, '\0') - 1;
	while (*src != '\0' && ft_strchr(set, *src))
		src++;
	while (end > src && ft_strchr(set, *end))
		end--;
	return (ft_substr(src, 0, end - src + 1));
}
