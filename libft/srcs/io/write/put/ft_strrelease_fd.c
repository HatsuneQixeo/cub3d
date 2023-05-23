/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrelease_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 20:04:10 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:48 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_strrelease_fd(char *str, int fd)
{
	const int	len = ft_putstr_fd(str, fd);

	free(str);
	return (len);
}
