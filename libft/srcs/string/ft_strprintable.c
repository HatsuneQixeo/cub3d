/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprintable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:16:51 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libto.h"

static int	ft_padsize(const char *base)
{
	char	*nbr;
	size_t	size;

	nbr = ft_utoa_base(UINT8_MAX, base);
	if (nbr == NULL)
		return (0);
	size = ft_strlen(nbr);
	free(nbr);
	return (size);
}

static int	ft_setnpc(char *str, uint8_t npc, const char *base, int len_pad)
{
	char	*str_npc;

	str_npc = ft_utoa_base(npc, base);
	if (str_npc == NULL)
		return (0);
	*str++ = '\\';
	str_npc = ft_strcombine(ft_strcreate(*base, len_pad - ft_strlen(str_npc)),
			str_npc);
	ft_strlcpy(str, str_npc, len_pad + 1);
	free(str_npc);
	return (1 + len_pad);
}

// Convert non printable character to number
// This function does not support complex character ex:(”初音ミク“)
char	*ft_strprintable(const char *src, const char *base)
{
	char	*str_main;
	char	*tmp;
	int		len_pad;
	size_t	len_printable;

	if (src == NULL || base == NULL || !ft_validbase(base))
		return (NULL);
	len_pad = ft_padsize(base);
	len_printable = ft_strcount_chris(src, ft_isprint);
	str_main = malloc(len_printable
			+ ((ft_strlen(src) - len_printable) * (len_pad + 1)) + 1);
	if (str_main == NULL)
		return (NULL);
	tmp = str_main;
	while (*src != '\0')
		if (ft_isprint(*src))
			*str_main++ = *src++;
	else
		str_main += ft_setnpc(str_main, *src++, base, len_pad);
	*str_main = '\0';
	return (tmp);
}

static size_t	ft_memchr_countis(const void *src, t_ftis ft_is, size_t bytes)
{
	char	*ptr;
	size_t	count;

	if (src == NULL || ft_is == NULL )
		return (0);
	ptr = (char *)src;
	count = 0;
	while (bytes--)
		if (ft_is(*ptr++))
			count++;
	return (count);
}

char	*ft_memprintable(const void *src, const char *base, size_t bytes)
{
	char	*ptr_src;
	char	*str_main;
	char	*tmp;
	int		len_pad;
	size_t	len_printable;

	ptr_src = (char *)src;
	len_pad = ft_padsize(base);
	len_printable = ft_memchr_countis(src, ft_isprint, bytes);
	str_main = malloc(len_printable + ((bytes - len_printable) * (len_pad + 1))
			+ 1);
	if (str_main == NULL)
		return (NULL);
	tmp = str_main;
	while (bytes--)
		if (ft_isprint(*ptr_src))
			*str_main++ = *ptr_src++;
	else
		str_main += ft_setnpc(str_main, *ptr_src++, base, len_pad);
	*str_main = '\0';
	return (tmp);
}
