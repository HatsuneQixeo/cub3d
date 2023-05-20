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

int	hook_button_close(void)
{
	ft_putendl_fd("Game Closed", 2);
	if (!SAN)
		system("leaks -q cub3d");
	exit(EXIT_SUCCESS);
	return (0);
}

int	hook_log(const char *message)
{
	printf("%p\n", message);
	return (0);
}
