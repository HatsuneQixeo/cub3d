/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:56:53 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

char	*ft_strjoin(const char *str1, const char *str2)
{
	char	*str_main;
	size_t	len;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	else if (str1 == NULL)
		return (ft_strdup(str2));
	else if (str2 == NULL)
		return (ft_strdup(str1));
	len = ft_strlen(str1) + ft_strlen(str2) + 1;
	str_main = malloc(len);
	if (str_main == NULL)
		return (NULL);
	ft_strlcpy(str_main, str1, len);
	ft_strlcat(str_main, str2, len);
	return (str_main);
}

// Reverse str2 with str1, dedicated for strmodify
char	*ft_strrjoin(const char *str1, const char *str2)
{
	return (ft_strjoin(str2, str1));
}
