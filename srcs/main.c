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

t_point	point_rotate(const t_point point, const double angle)
{
	t_point	new_point;

	new_point.x = point.x * cos(angle) - point.y * sin(angle);
	new_point.y = point.x * sin(angle) + point.y * cos(angle);
	return (new_point);
}

void	point_log(const char *prefix, const t_point point)
{
	printf("%sx: %f, y: %f\n", prefix, point.x, point.y);
}

void	point_move(t_point *point, const t_point vector)
{
	const double	speed = 6;

	if (vector.x == 0 && vector.y == 0)
		return ;
	else if (vector.x != 0 && vector.y != 0)
		*point = point_add(*point, point_scale(vector, speed * .75));
	else
		*point = point_add(*point, point_scale(vector, speed * 1.2));
}

double	point_angle(const t_point point)
{
	return (atan2(point.y, point.x));
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

t_offset	offset_direction(const double direction)
{
	if (direction > 0)
		return (putoffset_inverted);
	else
		return (putoffset_default);
}

void	start_to_end(t_point *start, t_point *end,
			const t_point size, const t_point direction)
{
	ft_bzero(start, sizeof(*start));
	*end = size;
	if (direction.x < 0)
	{
		start->x = size.x - 1;
		end->x = -1;
	}
	if (direction.y < 0)
	{
		start->y = size.y - 1;
		end->y = -1;
	}
}

void	cast_a_ray(const t_mlx mlx, const t_point player, const t_point cursor)
{
	const t_point	direction = point_sub(player, cursor);
	const t_point	size = (t_point){
		.x = ft_max(fabs(direction.x), 1),
		.y = ft_max(fabs(direction.y), 1)
	};
	t_image			ray;
	t_point			start;
	t_point			end;

	ray = image_create(mlx.p_mlx, size, NULL, NULL);
	ft_assert(ray.data != NULL, "cast_a_ray: Image creation failed");
	ray.putoffset_x = offset_direction(direction.x);
	ray.putoffset_y = offset_direction(direction.y);
	start_to_end(&start, &end, size, direction);
	image_clear(ray);
	image_draw_line(ray, colour_from_rgba(255, 120, 100, 20), start, end);
	image_put(mlx, ray, player);
}

void	test_rotate(const t_point dir)
{
	static double	i = 0;

	printf("i: %f\n", i);
	point_log("Rotate: ", point_rotate(dir, i));
	i += 0.1;
}

/* Should Divide the speed if both key is being pressed */
// ft_printf("くるり廻る廻る廻る世界\n");
int	hook_loop(t_game *game)
{
	const t_point	vector = player_vector(game->keys);

	if (game->keys[Key_ESC] == Press)
		hook_button_close(EXIT_SUCCESS);
	point_move(&game->player.pos, vector);
	image_put(game->mlx, game->screen_buffer, (t_point){0, 0});
	if (display_mouse(game->mouse))
	{
		image_put(game->mlx, game->texture.mouse_icon, game->mouse.pos);
		if (game->mouse.left_click == Press)
			cast_a_ray(game->mlx, game->player.pos, game->mouse.pos);
	}
	image_put(game->mlx, game->texture.player_icon, game->player.pos);
	// test_rotate(game->player.dir);
	/* Show angle */
	{
		// const double	angle = point_angle(point_sub(game->mouse.pos, prev_pos));
		// if (angle != 0)
		// 	printf("angle: %f\n", angle);
	}
	/* Show the mouse position */
	{
		// point_log("Motion: ", game->mouse.pos);
	}
	/* Show the mouse speed */
	{
		static t_point	prev_pos;

		if (ft_memcmp(&game->mouse.pos, &prev_pos, sizeof(t_point)))
			point_log("speed: ", point_sub(game->mouse.pos, prev_pos));
		prev_pos = game->mouse.pos;
	}
	/*
		Rotation seems to be on point,
		should be able to draw a line starting with player position,
		and (sum a scaled direction vector with player pos) as end
	*/
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
