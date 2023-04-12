/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook.h"
#include "libft.h"

int	hook_button_close(const int status)
{
	ft_putendl_fd("Game Closed", 2);
	// if (!SAN)
	// 	system("leaks -q cub3d");
	exit(status);
	return (0);
}

int	hook_log(const char *message)
{
	ft_printf("%s\n", message);
	return (0);
}
