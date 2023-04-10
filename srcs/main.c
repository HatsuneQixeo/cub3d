/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/10 22:58:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hook_loop(t_keys keys)
{
	const t_point	vector = player_vector(keys);
	// const int	*keys = ptr;

	// ft_printf("くるり廻る廻る廻る世界\n");
	// if (vector.x || vector.y)
	// 	printf("vector.x = %f, vector.y = %f\n", vector.x, vector.y);
	if (keys[Key_ESC] == Press)
		hook_button_close(0, EXIT_SUCCESS);
	return (0);
}

enum e_screen_size
{
	ScreenWidth = 1280,
	ScreenHeight = 720,
	BorderWidth = ScreenWidth / 10,
	BorderHeight = ScreenHeight / 10
};

/* Initialization and assertion */
t_game	game_init(void)
{
	t_game	game;

	game.mlx.p_mlx = mlx_init();
	ft_assert(game.mlx.p_mlx != NULL, "mlx_init() failed");
	game.mlx.p_win = mlx_new_window(game.mlx.p_mlx, ScreenWidth, ScreenHeight, "cub3d");
	ft_assert(game.mlx.p_win != NULL, "mlx_new_window() failed");
	game.screen_buffer = image_create(game.mlx.p_mlx,
			(t_size){.x = ScreenWidth, .y = ScreenHeight});
	ft_assert(game.screen_buffer.p_image != NULL,
		"image_create() for screen_buffer failed");
	ft_memset(&game.keys, Release, sizeof(game.keys));
	// game.map
	// game.player
	// game.texture
	return (game);
}

/* Outline */
void	image_draw_circle(t_image *image, const t_colour colour, const t_size center, const int radius)
{
	t_size	point;
	int		error;

	point.x = 0;
	point.y = radius;
	error = 1 - radius;
	while (point.x <= point.y)
	{
		image_draw_pixel(image, colour, (t_size){center.x + point.x, center.y + point.y});
		image_draw_pixel(image, colour, (t_size){center.x + point.y, center.y + point.x});
		image_draw_pixel(image, colour, (t_size){center.x - point.x, center.y + point.y});
		image_draw_pixel(image, colour, (t_size){center.x - point.y, center.y + point.x});
		image_draw_pixel(image, colour, (t_size){center.x + point.x, center.y - point.y});
		image_draw_pixel(image, colour, (t_size){center.x + point.y, center.y - point.x});
		image_draw_pixel(image, colour, (t_size){center.x - point.x, center.y - point.y});
		image_draw_pixel(image, colour, (t_size){center.x - point.y, center.y - point.x});
		if (error <= 0)
		{
			error += 2 * point.x + 1;
			point.x++;
		}
		else
		{
			error += 2 * (point.x - point.y) + 1;
			point.x++;
			point.y--;
		}
	}
}

int	main(void)
{
	t_game	game;
	t_mlx	mlx;
	
	game = game_init();
	mlx = game.mlx;
	/* Rendering test */
	{
		image_fill(&game.screen_buffer, 0x50ffffff);
		image_put(mlx, &game.screen_buffer, (t_size){.x = 0, .y = 0});
		// image_fill(&game.screen_buffer, colour_from_rgba(20, 160, 180, 50));
		image_fill(&game.screen_buffer, colour_from_percentage(.1, .9, .8, .4));
		// image_draw_rectangle(&game.screen_buffer, colour_from_rgba(20, 160, 180, 180),
		image_draw_rectangle(&game.screen_buffer, colour_from_percentage(.1, .8, .8, .7),
				(t_size){.x = BorderWidth, .y = BorderHeight},
				(t_size){.x = ScreenWidth - BorderWidth, .y = ScreenHeight - BorderHeight});
		image_draw_line(&game.screen_buffer, colour_from_rgba(0, 0, 0, 0),
				(t_size){.x = BorderWidth, .y = BorderHeight},
				(t_size){.x = ScreenWidth - BorderWidth, .y = ScreenHeight - BorderHeight});
		image_put(mlx, &game.screen_buffer, (t_size){.x = 0, .y = 0});
		image_draw_circle(&game.screen_buffer, colour_from_percentage(0.2, 0.4, 0.9, 0.6),
				(t_size){.x = ScreenWidth / 2, .y = ScreenHeight / 2}, 100);
		image_put(mlx, &game.screen_buffer, (t_size){.x = 0, .y = 0});
	}
	/* hook and loop */
	{
		mlx_do_key_autorepeatoff(mlx.p_mlx);
		mlx_hook(mlx.p_win, DestroyNotify, NoEventMask, hook_button_close,
			EXIT_SUCCESS);
		mlx_hook(mlx.p_win, KeyPress, NoEventMask, hook_key_press, game.keys);
		mlx_hook(mlx.p_win, KeyRelease, NoEventMask, hook_key_release, game.keys);
		mlx_loop_hook(mlx.p_mlx, hook_loop, game.keys);
	}
	mlx_loop(mlx.p_mlx);
}
