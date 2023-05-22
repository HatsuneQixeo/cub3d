/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	cub3d_runtime_assertion(const int condition, const char *attachment)
{
	if (condition)
		return ;
	ft_putendl_fd("Error", 2);
	perror(attachment);
	exit(1);
}
