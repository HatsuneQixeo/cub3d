/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion_numeric.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:49:44 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

typedef unsigned long long	t_too_long;

static t_too_long	ft_ulength(t_too_long nbr, const t_flags *flags)
{
	if (flags->mod_z)
		return ((size_t)nbr);
	else if (flags->mod_long & 0b1)
		return ((unsigned long)nbr);
	else if (flags->mod_long)
		return ((t_too_long)nbr);
	else if (flags->mod_short & 0b1)
		return ((unsigned short)nbr);
	else if (flags->mod_short)
		return ((unsigned char)nbr);
	else
		return ((unsigned int)nbr);
}

static long long	ft_dlength(long long nbr, const t_flags *flags)
{
	if (flags->mod_long & 0b1)
		return ((long)nbr);
	else if (flags->mod_long)
		return ((long long)nbr);
	else if (flags->mod_short & 0b1)
		return ((short)nbr);
	else if (flags->mod_short)
		return ((char)nbr);
	else
		return ((int)nbr);
}

char	*ft_decimal(long long d, const t_flags *flags)
{
	char	*nbr;

	d = ft_dlength(d, flags);
	nbr = ft_lltoa(d);
	if (d < 0)
		return (nbr);
	else if (flags->plus)
		return (ft_strmodify(ft_strrjoin, nbr, "+"));
	else if (flags->space)
		return (ft_strmodify(ft_strrjoin, nbr, " "));
	else
		return (nbr);
}

char	*ft_unsigned(unsigned long long hex, const t_flags *flags)
{
	char	*str;

	hex = ft_ulength(hex, flags);
	if (flags->format == 'u')
		return (ft_utoa_base(hex, DECIMAL));
	else if (flags->format == 'x')
		str = ft_utoa_base(hex, HEXADECIMAL);
	else if (flags->format == 'X')
		str = ft_utoa_base(hex, UPPERHEX);
	else if (flags->format == 'o')
		str = ft_utoa_base(hex, OCTAL);
	else
		return (NULL);
	if (*str == '0' || !flags->sharp)
		return (str);
	else if (flags->format == 'x')
		return (ft_strmodify(ft_strrjoin, str, "0x"));
	else if (flags->format == 'X')
		return (ft_strmodify(ft_strrjoin, str, "0X"));
	else if (flags->format == 'o')
		return (ft_strmodify(ft_strrjoin, str, "0"));
	else
		return (str);
}
