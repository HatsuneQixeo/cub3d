/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprintable_sign.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:18:04 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

static int	ft_setnpc_sign(char *str, uint8_t npc)
{
	*str++ = '\\';
	if (npc == '\b')
		*str = 'b';
	else if (npc == '\f')
		*str = 'f';
	else if (npc == '\n')
		*str = 'n';
	else if (npc == '\r')
		*str = 'r';
	else if (npc == '\t')
		*str = 't';
	else
		*str = '0';
	return (2);
}

//Undefined character are represent as '0'
char	*ft_strprintable_sign(const char *src)
{
	char	*str_main;
	char	*tmp;
	size_t	len_printable;

	len_printable = ft_strcount_chris(src, ft_isprint);
	str_main = malloc(len_printable + (ft_strlen(src) - len_printable) * 2 + 1);
	if (str_main == NULL)
		return (NULL);
	tmp = str_main;
	while (*src != '\0')
		if (ft_isprint(*src))
			*str_main++ = *src++;
	else
		str_main += ft_setnpc_sign(str_main, *src++);
	*str_main = '\0';
	return (tmp);
}
