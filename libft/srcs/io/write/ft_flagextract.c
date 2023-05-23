/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flagextract.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:05:19 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static int	ft_atoflag(const char **str, char *flag, int saved, va_list args)
{
	int	value;

	if (flag != NULL)
		*flag = 1;
	if (*++(*str) == '*')
		return (va_arg(args, int));
	value = 0;
	while (ft_isdigit(**str))
		value = (value * 10) + (*(*str)++ - '0');
	(*str)--;
	if (value == 0)
		return (saved);
	return (value);
}

static void	ft_width(const char **str, t_flags *flags, va_list args)
{
	if (**str == '-')
		flags->negative_field = 1;
	else if (**str == '0')
		flags->zero = 1;
	else if (ft_isdigit(**str) || **str == '*')
		(*str)--;
	else
		return ;
	flags->width = ft_atoflag(str, NULL, flags->width, args);
	if (flags->width < 0)
	{
		flags->width *= -1;
		flags->negative_field = 1;
	}
}

static void	ft_length_modifier(char c, t_flags *flags)
{
	if (c == 'z')
		flags->mod_z = 1;
	else if (c == 'l')
		flags->mod_long += 1;
	else if (c == 'h')
		flags->mod_short += 1;
}

char	*ft_flagextract(const char *str, t_flags *flags, va_list args)
{
	ft_bzero(flags, sizeof(t_flags));
	while (*++str != '\0'
		&& (ft_strchr("-+ #.*,;:_zlh", *str) || ft_isdigit(*str)))
	{
		if (*str == '#')
			flags->sharp = 1;
		else if (*str == '+')
			flags->plus = 1;
		else if (*str == ' ')
			flags->space = 1;
		else if (ft_strchr("zlh", *str))
			ft_length_modifier(*str, flags);
		else if (*str == '.')
			flags->precision = ft_atoflag(&str, &flags->period, 0, args);
		else
			ft_width(&str, flags, args);
	}
	if (flags->precision < 0)
	{
		flags->period = 0;
		flags->precision = 0;
	}
	flags->format = *str;
	return ((char *)str);
}
