/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount_chris.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:16:44 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

size_t	ft_strcount_chris(const char *str, t_ftis ft_is)
{
	size_t	count;

	if (str == NULL || ft_is == NULL)
		return (0);
	count = 0;
	str--;
	while (*++str != '\0')
		if (ft_is(*str))
			count++;
	return (count);
}
