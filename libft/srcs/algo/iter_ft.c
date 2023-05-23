/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:59:58 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libalgo.h"
#include "ft_printf.h"

const char	*iter_name(const char *newname)
{
	static const char	*name = ITNAME_DEFAULT;

	if (newname != NULL)
		name = newname;
	return (name);
}

void	iter_showstr(void *content)
{
	ft_dprintf(2, "%s: [%s]\n", iter_name(NULL), content);
}

void	iter_puterrendl(void *str)
{
	ft_putendl_fd(str, 2);
}
