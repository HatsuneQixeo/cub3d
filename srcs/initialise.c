/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:47 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_init(void *p_mlx, t_texture *texture, const t_map *map);

static int	hook_expose(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx.p_win, &x, &y);
	game->mouse.pos = (t_point){.x = x, .y = y};
	game->mouse.prev_pos = game->mouse.pos;
	game->mouse.focus = 1;
	return (0);
}

static void	ft_mlx_hook(void *win_ptr, int x_event, int (*func)(), void *param)
{
	mlx_hook(win_ptr, x_event, NoEventMask, func, param);
}

static void	events(t_game *game)
{
	const t_mlx	mlx = game->mlx;

	mlx_do_key_autorepeatoff(mlx.p_mlx);
	ft_mlx_hook(mlx.p_win, DestroyNotify, hook_button_close, EXIT_SUCCESS);
	ft_mlx_hook(mlx.p_win, KeyPress, hook_key_press, game->keys);
	ft_mlx_hook(mlx.p_win, KeyRelease, hook_key_release, game->keys);
	ft_mlx_hook(mlx.p_win, MotionNotify, hook_mouse_move, &game->mouse);
	ft_mlx_hook(mlx.p_win, Expose, hook_expose, game);
	mlx_loop_hook(mlx.p_mlx, hook_loop, game);
}

/* Initialization and assertion */
int	game_init(const char *path, t_game *game)
{
	game->mlx.p_mlx = mlx_init();
	cub3d_runtime_assertion(game->mlx.p_mlx != NULL, "mlx_init");
	if (cubmap_getmap(game->mlx.p_mlx, path, &game->map, &game->texture) == -1
		|| cubmap_player_init(game->map, &game->map.player) == -1)
		return (-1);
	texture_init(game->mlx.p_mlx, &game->texture, &game->map);
	cubmap_door_init(&game->map, game->texture.door_animation_len);
	cub3d_runtime_assertion(game->map.arr_doors != NULL, "arr_doors");
	game->screen_buffer = image_create(game->mlx.p_mlx,
			(t_point){.x = ScreenWidth, .y = ScreenHeight},
			(t_point){0, 0});
	cub3d_runtime_assertion(image_good(&game->screen_buffer),
		"screen_buffer creation");
	ft_intset((int *)game->keys, key_count, Release);
	game->mlx.p_win = mlx_new_window(game->mlx.p_mlx, ScreenWidth, ScreenHeight,
			"cub3d");
	cub3d_runtime_assertion(game->mlx.p_win != NULL, "mlx_new_window");
	game->mouse.focus = 1;
	events(game);
	return (0);
}
