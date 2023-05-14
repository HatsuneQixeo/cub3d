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
#include "minimap.h"

t_point	minimap_scale_point(const t_point point)
{
	return (point_upscale(point, MapCellSize + 1));
}

void	map_draw_tile(t_image *map, const t_colour colour, const t_point pos)
{
	const t_point	map_start = point_upscale(pos, MapCellSize + 1);
	const t_point	map_end = point_add(map_start,
			(t_point){MapCellSize, MapCellSize});

	image_draw_rectangle(map, colour, map_start, map_end);
}

t_image	map_texture(void *p_mlx, const t_map map)
{
	const t_colour	wall_colour = colour_from_percentage(.70, .90, .90, .70);
	const t_colour	space_colour = colour_from_percentage(.20, .30, .40, .70);
	const t_point	size = point_add((t_point){-1, -1},
			point_upscale(map.size, MapCellSize + 1));
	t_image			image;
	t_point			it;

	image = image_create(p_mlx, size, point_apply(size, putoffset_inverted));
	if (image.data == NULL)
		return (image);
	image_fill(&image, colour_from_percentage(.0, .20, .20, .50));
	it.y = -1;
	while (++it.y < map.size.y)
	{
		it.x = -1;
		while (++it.x < map.size.x)
		{
			if (map.layout[(int)it.y][(int)it.x] == '1')
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
		const t_point	size = {17, 17};

		texture->player_icon = image_create(p_mlx, size,
				point_apply(size, putoffset_centered));
		ft_assert(texture->player_icon.p_image != NULL,
			"image_create() for player_icon failed");
		image_fill_circle(&texture->player_icon,
			colour_from_percentage(.2, .9, .6, .60));
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
	{
		texture->walls[Invalid] = image_create(p_mlx, (t_point){1, 1}, (t_point){0, 0});
		ft_assert(texture->walls[Invalid].p_image != NULL,
			"image_create() for invalid texture failed");
		texture->walls[Invalid].data[0] = 0x00000000;
	}
}

/* Initialization and assertion */
int	game_init(const char *path, t_game *game)
{
	game->mlx.p_mlx = mlx_init();
	ft_assert(game->mlx.p_mlx != NULL, "mlx_init() failed");
	if (cubmap_getmap(game->mlx.p_mlx, path, &game->map, &game->texture) == -1)
		return (-1);
	game->screen_buffer = image_create(game->mlx.p_mlx,
			(t_point){.x = ScreenWidth, .y = ScreenHeight},
			(t_point){0, 0});
	ft_assert(game->screen_buffer.p_image != NULL,
		"image_create() for screen_buffer failed");
	ft_intset((int *)game->keys, key_count, Release);
	texture_init(game->mlx.p_mlx, game->map, &game->texture);
	game->player = cubmap_getplayer(game->map); 
	game->mouse.left_click = Release;
	game->mlx.p_win = mlx_new_window(game->mlx.p_mlx, ScreenWidth, ScreenHeight, "Miku love cub3d");
	ft_assert(game->mlx.p_win != NULL, "mlx_new_window() failed");
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
