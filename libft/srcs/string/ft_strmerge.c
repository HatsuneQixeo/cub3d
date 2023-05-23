/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:24:04 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdarg.h>
#include "libstring.h"
#include "liblinked_list.h"
#include "libto.h"

char	*strmerge_format(va_list args, const char format)
{
	char		*arg;
	const char	format_lower = ft_tolower(format);

	if (format_lower == 's')
		arg = ft_strdup(va_arg(args, char *));
	else if (format_lower == 'f')
		arg = va_arg(args, char *);
	else
		return (ft_substr(&format, 0, 1));
	if (ft_isupper(format))
		ft_striteri(arg, iteri_toupper);
	return (arg);
}

char	*ft_strmerge(const char *str_format, ...)
{
	va_list		args;
	t_list		*lst_buffer;
	const char	*format_specifier = ft_strchr(str_format, '%');

	va_start(args, str_format);
	lst_buffer = NULL;
	while (format_specifier != NULL && format_specifier[1] != '\0')
	{
		ft_lstadd_back(&lst_buffer, ft_lstnew(
				ft_substr(str_format, 0, format_specifier - str_format)));
		ft_lstadd_back(&lst_buffer, ft_lstnew(
				strmerge_format(args, format_specifier[1])));
		str_format = format_specifier + 2;
		format_specifier = ft_strchr(str_format, '%');
	}
	ft_lstadd_back(&lst_buffer, ft_lstnew(
			ft_substr(str_format, 0, format_specifier - str_format)));
	va_end(args);
	return (ft_lsttostr_clear(&lst_buffer));
}
