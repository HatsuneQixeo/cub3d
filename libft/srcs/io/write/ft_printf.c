/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 00:48:43 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

/**
 * @brief 
 * 
 * Tester
 * https://github.com/gavinfielder/pft
 * 
 * @param fd 
 * @param str 
 * @param args 
 * @return int 
 * 
 * @bug Return -(1 + (number_of_conversions * 2)) if the given fd is invalid
 * I do not want to know how to handle if the given fd is closed while printing
 * 
 * IDEA:
 * Maybe I can store everything in a buffer
 * and flush it at the end of the function?
 * It will be more efficient too
 * Will I do it? (lol no, like I'm ever using this garbage again)
 */
int	ft_printf_core(int fd, const char *str, va_list args)
{
	int		len_total;
	char	*ptr_conversion;
	t_flags	flags;

	len_total = 0;
	ptr_conversion = ft_strchr(str, '%');
	while (ptr_conversion != NULL)
	{
		len_total += write(fd, str, ptr_conversion - str);
		str = ft_flagextract(ptr_conversion, &flags, args);
		if (flags.format == '\0')
			break ;
		len_total += ft_conversion(fd, args, &flags);
		ptr_conversion = ft_strchr(++str, '%');
	}
	return (len_total + ft_putstr_fd(str, fd));
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		ret;

	va_start(args, str);
	ret = ft_printf_core(1, str, args);
	va_end(args);
	return (ret);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	args;
	int		ret;

	va_start(args, str);
	ret = ft_printf_core(fd, str, args);
	va_end(args);
	return (ret);
}
