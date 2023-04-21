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

t_image	map_texture(void *p_mlx, const t_map map)
{
	const t_colour	wall_colour = colour_from_percentage(.70, .90, .90, .70);
	const t_colour	space_colour = colour_from_percentage(.20, .30, .40, .70);
	t_image			image;
	t_point			it;

	image = image_create(p_mlx, point_add(point_scale(map.size, MapCellSize), map.size),
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
				image_draw_rectangle(&image, wall_colour,
					point_add(point_scale(it, MapCellSize), it),
					point_add(point_scale(point_add(it, (t_point){1, 1}), MapCellSize), it));
			else
				image_draw_rectangle(&image, space_colour,
					point_add(point_scale(it, MapCellSize), it),
					point_add(point_scale(point_add(it, (t_point){1, 1}), MapCellSize), it));
		}
	}
	return (image);
}

static t_texture	texture_init(void *p_mlx, const t_map map)
{
	t_texture	texture;

	ft_bzero(&texture, sizeof(t_texture));
	{
		texture.player_icon = image_create(p_mlx, (t_point){.x = 17, .y = 17},
				putoffset_centered, putoffset_centered);
		ft_assert(texture.player_icon.p_image != NULL,
			"image_create() for player_icon failed");
		image_fill_circle(&texture.player_icon,
			colour_from_percentage(.3, .7, .5, .75));
	}
	{
		texture.mouse_icon = image_readxpm(p_mlx, "sprites/Normal-Select.xpm",
				putoffset_default, putoffset_default);
		ft_assert(texture.mouse_icon.p_image != NULL,
			"image_readxpm() for mouse_icon failed");
		// texture.mouse_icon = image_create(p_mlx, (t_point){.x = 25, .y = 25},
		// 		putoffset_centered, putoffset_centered);
		// image_fill_circle(texture.mouse_icon,
		// 	colour_from_percentage(.3, .7, .8, .75));
	}
	{
		texture.map = map_texture(p_mlx, map);
		ft_assert(texture.map.p_image != NULL,
			"image_create() for map failed");
	}
	return (texture);
}

static t_mouse	mouse_init(void *p_win)
{
	t_mouse	mouse;

	// mlx_mouse_move(p_win, ScreenWidth / 2, ScreenHeight / 2);
	// mouse.press = (t_point){.x = -1, .y = -1};
	mouse.left_click = Release;
	return (mouse);
}

t_map	beta_map(void)
{
	t_map	map;
	map.layout = ft_strlistdup((char *[]) {
#if 1
			"111111111",
			"100010001",
			"100011011",
			"100010001",
			"110110001",
			"100000001",
			"100010111",
			"100010001",
			"111111111",
#else
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
			NULL
		});
	map.size = (t_point){
		.x = ft_strlen(map.layout[0]),
		.y = ft_strcount(map.layout)
	};
	return (map);
}

/* Initialization and assertion */
t_game	game_init(void)
{
	t_game		game;
	const t_mlx	mlx = {
		.p_mlx = mlx_init(),
		.p_win = mlx_new_window(mlx.p_mlx, ScreenWidth, ScreenHeight, "cub3d")
	};

	ft_bzero(&game, sizeof(t_game));
	ft_assert(mlx.p_mlx != NULL, "mlx_init() failed");
	ft_assert(mlx.p_win != NULL, "mlx_new_window() failed");
	game.mlx = mlx;
	game.screen_buffer = image_create(game.mlx.p_mlx,
			(t_point){.x = ScreenWidth, .y = ScreenHeight},
			putoffset_default, putoffset_default);
	ft_assert(game.screen_buffer.p_image != NULL,
		"image_create() for screen_buffer failed");
	game.mouse = mouse_init(game.mlx.p_win);
	ft_intset(game.keys, key_count, Release);
	game.map = beta_map();
	game.texture = texture_init(game.mlx.p_mlx, game.map);
	// game.map /* In map parsing */
	// game.player /* In map parsing */
	return (game);
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

/* Temporary background */
void	beta_screen_buffer(t_image buffer)
{
	const t_point	topleft = {
		.x = ScreenBorderWidth,
		.y = ScreenBorderHeight
	};
	const t_point	bottomright = {
		.x = ScreenWidth - ScreenBorderWidth,
		.y = ScreenHeight - ScreenBorderHeight
	};
	const t_point	topright = {
		.x = ScreenWidth - ScreenBorderWidth,
		.y = ScreenBorderHeight
	};
	const t_point	bottomleft = {
		.x = ScreenBorderWidth,
		.y = ScreenHeight - ScreenBorderHeight
	};
	const t_point	center = {
		.x = ScreenWidth / 2,
		.y = ScreenHeight / 2
	};

	image_fill(&buffer, colour_from_percentage(.1, .5, .5, .4));
	image_draw_rectangle(&buffer, colour_from_percentage(.1, .3, .35, .60),
		topleft, bottomright);
	// for (unsigned int i = 1; i < buffer.size.y; i += 2)
	// {
	// 	image_draw_line(&buffer, colour_from_rgba(200, 50, 50, 40), (t_point){.x = 0, .y = i}, (t_point){.x = buffer.size.x, .y = i});
	// }

	image_draw_line(&buffer, colour_from_rgba(0, 0, 0, 0), bottomright, topleft);
	image_draw_line(&buffer, colour_from_rgba(0, 0, 0, 0), topright, bottomleft);
	image_draw_line(&buffer, colour_from_rgba(0, 0, 0, 0),
		(t_point){.x = center.x, .y = bottomleft.y},
		(t_point){.x = center.x, .y = topleft.y});
	image_draw_line(&buffer, colour_from_rgba(0, 0, 0, 0),
		(t_point){.x = topright.x, .y = center.y},
		(t_point){.x = topleft.x, .y = center.y});
	draw_filled_circle(&buffer, colour_from_percentage(0.2, 0.4, 0.9, 0.3),
		(t_point){.x = center.x + center.x / 2, .y = center.y}, 100);
	image_draw_circle(&buffer, colour_from_percentage(0.2, 0.4, 0.9, 0.3),
		(t_point){.x = center.x - center.x / 2, .y = center.y}, 100);
}
