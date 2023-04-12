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

static t_texture	texture_init(void *p_mlx)
{
	t_texture	texture;

	ft_bzero(&texture, sizeof(t_texture));
	texture.player_icon = image_create(p_mlx, (t_point){.x = 17, .y = 17},
			putoffset_centered, putoffset_centered);
	image_fill_circle(texture.player_icon,
		colour_from_percentage(.3, .7, .5, .75));
	texture.mouse_icon = image_create(p_mlx, (t_point){.x = 25, .y = 25},
			putoffset_centered, putoffset_centered);
	image_fill_circle(texture.mouse_icon,
		colour_from_percentage(.3, .7, .8, .75));
	return (texture);
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
	game.texture = texture_init(game.mlx.p_mlx);
	{
		game.mouse.pos = (t_point){.x = -1, .y = -1};
		game.mouse.press = (t_point){.x = -1, .y = -1};
		game.mouse.left_click = Release;
	}
	ft_intset(game.keys, key_count, Release);
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
	ft_mlx_hook(mlx.p_win, MotionNotify, hook_mouse_move, &game->mouse.pos);
	/* Gotta have to dig into this */
	// mlx_do_sync(mlx.p_mlx);
	mlx_loop_hook(mlx.p_mlx, hook_loop, game);
}

/* Temporary background */
void	beta_screen_buffer(t_image buffer)
{
	const t_point	topleft = {
		.x = BorderWidth,
		.y = BorderHeight
	};
	const t_point	bottomright = {
		.x = ScreenWidth - BorderWidth,
		.y = ScreenHeight - BorderHeight
	};
	const t_point	topright = {
		.x = ScreenWidth - BorderWidth,
		.y = BorderHeight
	};
	const t_point	bottomleft = {
		.x = BorderWidth,
		.y = ScreenHeight - BorderHeight
	};
	const t_point	center = {
		.x = ScreenWidth / 2,
		.y = ScreenHeight / 2
	};

	image_fill(buffer, colour_from_percentage(.1, .5, .5, .4));
	image_draw_rectangle(buffer, colour_from_percentage(.1, .3, .35, .39),
		topleft, bottomright);
	image_draw_line(buffer, colour_from_rgba(0, 0, 0, 0), bottomright, topleft);
	image_draw_line(buffer, colour_from_rgba(0, 0, 0, 0), topright, bottomleft);
	image_draw_line(buffer, colour_from_rgba(0, 0, 0, 0),
		(t_point){.x = center.x, .y = bottomleft.y},
		(t_point){.x = center.x, .y = topleft.y});
	image_draw_line(buffer, colour_from_rgba(0, 0, 0, 0),
		(t_point){.x = topright.x, .y = center.y},
		(t_point){.x = topleft.x, .y = center.y});
	draw_filled_circle(buffer, colour_from_percentage(0.2, 0.4, 0.9, 0.3),
		(t_point){.x = center.x + center.x / 2, .y = center.y}, 100);
	image_draw_circle(buffer, colour_from_percentage(0.2, 0.4, 0.9, 0.3),
		(t_point){.x = center.x - center.x / 2, .y = center.y}, 100);
}
