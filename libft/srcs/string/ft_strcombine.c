/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcombine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:40:45 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

char	*ft_strcombine(char *str1, char *str2)
{
	char	*str_combined;

	if (str1 == NULL)
		return (str2);
	else if (str2 == NULL)
		return (str1);
	str_combined = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (str_combined);
}
