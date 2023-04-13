/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	point_move_player(t_point *point, const t_point vector)
{
	const double	speed = 6;

	if (vector.x == 0 && vector.y == 0)
		return ;
	else if (vector.x != 0 && vector.y != 0)
		*point = point_add(*point, point_scale(vector, speed * .75));
	else
		*point = point_add(*point, point_scale(vector, speed * 1.2));
}

int	display_mouse(const t_mouse mouse)
{
	static int	custom_cursor = 0;
	const int	in_screen = (unsigned int)mouse.pos.x < ScreenWidth
		&& (unsigned int)mouse.pos.y < ScreenHeight;

	if (in_screen != custom_cursor)
	{
		custom_cursor = in_screen;
		(int (*[])(void)){mlx_mouse_show, mlx_mouse_hide}[custom_cursor]();
	}
	return (custom_cursor);
}

/* Just a tool for adjusting background colour */
void	put_background(t_mlx mlx)
{
	const t_point	size = (t_point){ScreenWidth, ScreenHeight};
	t_image			image;
	const t_colour	colour = colour_from_rgba(200, 255, 255, 210);

	image = image_create(mlx.p_mlx, size, putoffset_default, putoffset_default);
	image_fill(image, colour);
	image_put(mlx, image, (t_point){0, 0});
	image_destroy(mlx.p_mlx, &image);
}

void	player_rotate(t_point *dir, const t_mouse mouse, const t_keys keys)
{
	const int		key_direction = ((keys[Key_Left] == Press) * -1)
				+ (keys[Key_Right] == Press);
	const double	mouse_speed = (mouse.pos.x - mouse.prev_pos.x) *.00831;

	*dir = point_rotate(*dir, key_direction * 0.039);
	*dir = point_rotate(*dir, mouse_speed);
}

// ft_printf("くるり廻る廻る廻る世界\n");
int	hook_loop(t_game *game)
{
	if (game->keys[Key_ESC] == Press)
		hook_button_close(EXIT_SUCCESS);
	/* Todo: Should probably rotate the vector to fit the direction */
	point_move_player(&game->player.pos, player_vector(game->keys));
	/* Background render */
	{
		mlx_clear_window(game->mlx.p_mlx, game->mlx.p_win);
		put_background(game->mlx);
		image_put(game->mlx, game->screen_buffer, (t_point){0, 0});
		/* Minimap */
		image_put(game->mlx, game->texture.minimap, (t_point){0, 0});
	}
	if (display_mouse(game->mouse))
	{
		image_put(game->mlx, game->texture.mouse_icon, game->mouse.pos);
		if (game->mouse.left_click == Press)
			cast_a_ray(game->mlx, game->player.pos, point_sub(game->player.pos, game->mouse.pos));
	}
	image_put(game->mlx, game->texture.player_icon, game->player.pos);
	/* Show angle */
	{
		// const double	angle = point_angle(point_sub(game->mouse.pos, prev_pos));

		// if (angle != 0)
		// 	printf("angle: %f\n", angle);
	}
	/* Show the mouse speed */
	player_rotate(&game->player.dir, game->mouse, game->keys);
	/* Render the ray */
	cast_a_ray(game->mlx, game->player.pos, point_scale(game->player.dir, 831 / 2));
	game->mouse.prev_pos = game->mouse.pos;
	return (0);
}

int	main(void)
{
	t_game	game;
	t_image	image;

	game = game_init();
	game.player.pos = (t_point){0, 0};
	game.player.dir = (t_point){.x = 1, .y = 0}; /* N, S, E, W */
	/* A backgroud
		Might come in handy if you get annoyed by the trace
	*/
	// image_fill(game.screen_buffer, colour_from_rgba(100, 100, 100, 0));
	// image_put(game.mlx, game.screen_buffer, (t_point){0, 0});
	beta_screen_buffer(game.screen_buffer);
	events(&game);
	mlx_loop(game.mlx.p_mlx);
}
