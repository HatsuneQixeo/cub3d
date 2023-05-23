/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount_chrset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:16:47 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

size_t	ft_strcount_chrset(const char *str, const char *set)
{
	size_t	count;

	count = 0;
	if (*set == '\0')
		return (1);
	while (*str != '\0')
		if (ft_strchr(set, *str++))
			count++;
	return (count);
}
