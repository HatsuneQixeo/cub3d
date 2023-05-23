/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:56:42 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

char	*ft_strdup(const char *src)
{
	const size_t	len = ft_strlen(src) + 1;
	char *const		str = malloc(len);

	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, src, len);
	return (str);
}
