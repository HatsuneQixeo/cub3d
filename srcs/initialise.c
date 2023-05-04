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

void	map_draw_tile(t_image *map, const t_colour colour, const t_point pos)
{
	const t_point	map_start = point_upscale(pos, MapCellSize);
	const t_point	map_end = point_upscale(point_add(pos, (t_point){1, 1}),
				MapCellSize);

	image_draw_rectangle(map, colour,
		point_add(map_start, pos),
		point_add(map_end, pos));
}

t_image	map_texture(void *p_mlx, const t_map map)
{
	const t_colour	wall_colour = colour_from_percentage(.70, .90, .90, .70);
	const t_colour	space_colour = colour_from_percentage(.20, .30, .40, .70);
	t_image			image;
	t_point			it;

	image = image_create(p_mlx, point_add(point_upscale(map.size, MapCellSize),
				point_sub(map.size, (t_point){1, 1})),
			putoffset_inverted, putoffset_inverted);
	if (image.data == NULL)
		return (image);
	image_fill(&image, colour_from_percentage(.0, .20, .20, .50));
	it.y = -1;
	while (++it.y < map.size.y)
	{
		it.x = -1;
		while (++it.x < map.size.x)
		{
			if (map.layout[(unsigned int)it.y][(unsigned int)it.x] == '1')
				map_draw_tile(&image, wall_colour, it);
			else
				map_draw_tile(&image, space_colour, it);
		}
	}
	return (image);
}

static void	texture_init(void *p_mlx, const t_map map, t_texture *texture)
{
	{
		texture->player_icon = image_create(p_mlx, (t_point){.x = 17, .y = 17},
				putoffset_centered, putoffset_centered);
		ft_assert(texture->player_icon.p_image != NULL,
			"image_create() for player_icon failed");
		image_fill_circle(&texture->player_icon,
			colour_from_percentage(.3, .7, .5, .75));
	}
	{
		texture->mouse_icon = image_readxpm(p_mlx, "sprites/Normal-Select.xpm",
				putoffset_default, putoffset_default);
		ft_assert(texture->mouse_icon.p_image != NULL,
			"image_readxpm() for mouse_icon failed");
		// texture->mouse_icon = image_create(p_mlx, (t_point){.x = 25, .y = 25},
		// 		putoffset_centered, putoffset_centered);
		// image_fill_circle(texture->mouse_icon,
		// 	colour_from_percentage(.3, .7, .8, .75));
	}
	{
		texture->map = map_texture(p_mlx, map);
		ft_assert(texture->map.p_image != NULL,
			"image_create() for map failed");
	}
}

static t_mouse	mouse_init(void *p_win)
{
	t_mouse	mouse;

	// mlx_mouse_move(p_win, ScreenWidth / 2, ScreenHeight / 2);
	// mouse.press = (t_point){.x = -1, .y = -1};
	mouse.left_click = Release;
	return (mouse);
}

#if 0
			"111111111",
			"100010001",
			"100011011",
			"100010001",
			"110110001",
			"100000001",
			"100010111",
			"100010001",
			"111111111",
#elif 0
			"111111111111111",
			"100000010000001",
			"100000010000001",
			"100011111100111",
			"100000010000001",
			"100000010000001",
			"100000010000001",
			"110011110000001",
			"100000000000001",
			"100000000000001",
			"100000010011111",
			"100000010000001",
			"100000010000001",
			"100000010000001",
			"111111111111111",
#endif
int	cubmap_getmap(const char *path, t_game *game);

/* Initialization and assertion */
int	game_init(const char *path, t_game *game)
{
	const t_mlx	mlx = {
		.p_mlx = mlx_init(),
		.p_win = mlx_new_window(mlx.p_mlx, ScreenWidth, ScreenHeight, "cub3d")
	};

	game->mlx = mlx;
	if (cubmap_getmap(path, game) == -1)
		return (-1);
	ft_assert(game->mlx.p_mlx != NULL, "mlx_init() failed");
	ft_assert(game->mlx.p_win != NULL, "mlx_new_window() failed");
	game->screen_buffer = image_create(game->mlx.p_mlx,
			(t_point){.x = ScreenWidth, .y = ScreenHeight},
			putoffset_default, putoffset_default);
	ft_assert(game->screen_buffer.p_image != NULL,
		"image_create() for screen_buffer failed");
	game->mouse = mouse_init(game->mlx.p_win);
	ft_intset((int *)game->keys, key_count, Release);
	texture_init(game->mlx.p_mlx, game->map, &game->texture);
	// game->map /* In map parsing */
	// game->player /* In map parsing */
	return (0);
}

static void	ft_mlx_hook(void *win_ptr, int x_event, int (*func)(), void *param)
{
	mlx_hook(win_ptr, x_event, NoEventMask, func, param);
}

void	events(t_game *game)
{
	const t_mlx	mlx = game->mlx;

	/* hooks and loop */
	mlx_do_key_autorepeatoff(mlx.p_mlx);
	// for (int i = 2; i <= 36; i++)
		// ft_mlx_hook(mlx.p_win, i, hook_log, NULL);
	ft_mlx_hook(mlx.p_win, DestroyNotify, hook_button_close, EXIT_SUCCESS);
	ft_mlx_hook(mlx.p_win, KeyPress, hook_key_press, game->keys);
	ft_mlx_hook(mlx.p_win, KeyRelease, hook_key_release, game->keys);
	ft_mlx_hook(mlx.p_win, ButtonPress, hook_mouse_click, &game->mouse);
	ft_mlx_hook(mlx.p_win, ButtonRelease, hook_mouse_release, &game->mouse);
	ft_mlx_hook(mlx.p_win, Expose, hook_expose, game);
	ft_mlx_hook(mlx.p_win, MotionNotify, hook_mouse_move, &game->mouse.pos);
	/* Gotta have to dig into this */
	// mlx_do_sync(mlx.p_mlx);
	mlx_loop_hook(mlx.p_mlx, hook_loop, game);
}
