/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 20:46:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

char	*ft_strmapi(const char *src, char (*ft)(unsigned int, char))
{
	char	*strmap;
	size_t	i;

	strmap = malloc(ft_strlen(src) + 1);
	if (strmap == NULL)
		return (NULL);
	i = -1;
	while (src[++i] != '\0')
		strmap[i] = ft(i, src[i]);
	strmap[i] = '\0';
	return (strmap);
}
