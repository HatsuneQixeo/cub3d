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
#include "cub3d.h"

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
	printf("%p\n", message);
	return (0);
}

int	hook_expose(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx.p_win, &x, &y);
	game->mouse.pos = (t_point){.x = x, .y = y};
	game->mouse.prev_pos = game->mouse.pos;
	return (0);
}
