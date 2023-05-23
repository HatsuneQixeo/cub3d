/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:57:17 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*substr;

	if (str == NULL)
		return (NULL);
	else if (start >= ft_strlen(str) || len == 0)
		return (ft_strdup(""));
	else if (len > ft_strlen(str + start))
		return (ft_strdup(str + start));
	substr = malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	ft_strlcpy(substr, str + start, len + 1);
	return (substr);
}
