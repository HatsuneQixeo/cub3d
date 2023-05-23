/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmanipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:05:33 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_findsign(const char *str)
{
	if (ft_strchr("-+ ", *str))
		return (1);
	else if (!ft_strncmp(str, "0x", 2) || !ft_strncmp(str, "0X", 2))
		return (2);
	else
		return (0);
}

static char	*ft_period(char *str, const t_flags *flags)
{
	int	len_pad;
	int	sign;

	if (flags->format == 's' || flags->format == 'b')
	{
		if (ft_strlen(str) > (unsigned int)flags->precision)
			str[flags->precision] = '\0';
		return (str);
	}
	sign = ft_findsign(str);
	if (flags->precision == 0 && !ft_strcmp(&str[sign], "0")
		&& !(flags->format == 'o' && flags->sharp))
		str[sign] = '\0';
	len_pad = (flags->precision + sign) - ft_strlen(str);
	if (len_pad <= 0)
		return (str);
	return (ft_strcombine(ft_strcreate('0', len_pad), str));
}

static char	*ft_setsign(char *str, const t_flags *flags)
{
	char	*c_set;
	char	*c_sign;

	if (flags->format == 'u' || flags->format == 'o'
		|| flags->format == 's' || flags->format == 'b')
		return (str);
	c_set = ft_strskip_chr(str, ' ');
	c_sign = ft_strskip_chr(c_set, '0');
	if (*c_sign == '-' || *c_sign == '+'
		|| (*c_sign == ' ' && ft_isdigit(*(c_sign + 1))))
		ft_swapbyte(c_set, c_sign);
	else if (*c_sign == 'x' || *c_sign == 'X')
		ft_swapbyte(++c_set, c_sign);
	return (str);
}

char	*ft_strfinalize(char *str, const t_flags *flags)
{
	int	len_pad;

	if (flags->format == 'f')
		return (str);
	if (flags->period)
		str = ft_period(str, flags);
	if (flags->format == 'b')
		str = ft_strmodify(ft_strprintable, str, HEXADECIMAL);
	len_pad = flags->width - ft_strlen(str);
	if (len_pad <= 0)
		return (ft_setsign(str, flags));
	else if (flags->negative_field)
		str = ft_strcombine(str, ft_strcreate(' ', len_pad));
	else if (flags->zero && !flags->period)
		str = ft_strcombine(ft_strcreate('0', len_pad), str);
	else if (flags->width)
		str = ft_strcombine(ft_strcreate(' ', len_pad), str);
	return (ft_setsign(str, flags));
}
