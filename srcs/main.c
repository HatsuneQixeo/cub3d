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

	image = image_create(mlx.p_mlx, size, putoffset_default, putoffset_default);
	image_fill(&image, colour_from_rgba(200, 255, 255, 210));
	image_put(mlx, &image, (t_point){0, 0});
	image_destroy(mlx.p_mlx, &image);
}

#ifndef DEBUG
# define DEBUG	0
#endif

#define DEBUGI(value)	if (DEBUG) printf("%-20s: %d\n", #value, value)
#define DEBUGF(value)	if (DEBUG) printf("%-20s: %f\n", #value, value)
#define DEBUGPOINT(point)	if (DEBUG) point_log(#point": ", point)

void	raycast(t_mlx mlx, t_image *screen_buffer, const t_player *player, const t_map map)
{
	t_image			image_ray = image_create(mlx.p_mlx, screen_buffer->size,
			putoffset_default, putoffset_default);
	const t_point	plane = point_rotate(player->plane, point_angle(player->dir));
	const t_point	pos = player->pos;

	image_clear(&image_ray);
	for (unsigned int i = 0; i < ScreenWidth; i++)
	{
		DEBUGPOINT(pos);
		DEBUGPOINT(plane);

		if (DEBUG)
			printf("i: %i\n", i);
		const double	cameraX = -1 + (2 * i / (double)ScreenWidth);
		DEBUGF(cameraX);
		const t_point	scaled_plane = point_scale(plane, cameraX);
		DEBUGPOINT(scaled_plane);
		const t_point	ray_direction = point_add(player->dir, scaled_plane);
		DEBUGPOINT(player->dir);
		DEBUGPOINT(ray_direction);

		t_point	delta_distance = {
			.x = (ray_direction.x == 0) ? 1e30 : fabs(1 / ray_direction.x),
			.y = (ray_direction.y == 0) ? 1e30 : fabs(1 / ray_direction.y)
		};
		DEBUGPOINT(delta_distance);
		t_point	step;
		t_point	side_distance;

		if (ray_direction.x < 0)
		{
			step.x = -1;
			side_distance.x = (pos.x - trunc(pos.x)) * delta_distance.x;
		}
		else
		{
			step.x = 1;
			side_distance.x = (1 + (trunc(pos.x) - pos.x)) * delta_distance.x;
		}
		if (ray_direction.y < 0)
		{
			step.y = -1;
			side_distance.y = (pos.y - trunc(pos.y)) * delta_distance.y;
		}
		else
		{
			step.y = 1;
			side_distance.y = (1 + (trunc(pos.y) - pos.y)) * delta_distance.y;
		}
		DEBUGPOINT(side_distance);
		t_point	point_map = point_round(pos, trunc);

		int	side;
		while (map.layout[(int)point_map.y][(int)point_map.x] != '1')
		{
			if (side_distance.x < side_distance.y)
			{
				side_distance.x += delta_distance.x;
				point_map.x += step.x;
				side = 0;
			}
			else
			{
				side_distance.y += delta_distance.y;
				point_map.y += step.y;
				side = 1;
			}
		}
		DEBUGI(side);
		const double	collide_distance = (side ? (side_distance.y - delta_distance.y) : (side_distance.x - delta_distance.x));
		DEBUGF(collide_distance);

		const int	line_height = ScreenHeight / collide_distance;
		const int	draw_start = ft_max(0, (ScreenHeight - line_height) / 2);
		const int	draw_end = ft_min(ScreenHeight - 1, (line_height + ScreenHeight) / 2);

		DEBUGI(line_height);
		DEBUGI(draw_start);
		DEBUGI(draw_end);
		if (DEBUG)
			printf("\n");
		image_draw_line(&image_ray, colour_from_rgba(20, 150, 180, 39),
			(t_point){.x = i, .y = draw_start},
			(t_point){.x = i, .y = draw_end});
	}
	image_put(mlx, &image_ray, (t_point){0, 0});
	image_destroy(mlx.p_mlx, &image_ray);
}

/* Doesn't work the way I think because the map is not always rectangular */
void	put_minimap(t_mlx mlx, const t_image *map, const t_player *player, const t_image *player_icon)
{
	const t_point	player_map_pos = point_scale(player->pos, MapCellSize);

	/* Sectioned Minimap */
	{
		t_image			image;

		image = image_create(mlx.p_mlx, (t_point){MinimapLength, MinimapLength},
				putoffset_default, putoffset_default);
		image_clear(&image);
		t_point	start = {
			.x = ft_max(0, player_map_pos.x - (image.size.x / 2)),
			.y = ft_max(0, player_map_pos.y - (image.size.y / 2))
		};
		const t_point	end = {
			.x = ft_min(map->size.x, start.x + image.size.x),
			.y = ft_min(map->size.y, start.y + image.size.y)
		};

		if (end.x - start.x < image.size.x)
			start.x = ft_max(0, map->size.x - image.size.x);
		if (end.y - start.y < image.size.y)
			start.y = ft_max(0, map->size.y - image.size.y);
		t_point	it;
		it.y = start.y - 1;
		while (++it.y < end.y)
		{
			it.x = start.x - 1;
			while (++it.x < end.x)
				image_draw_pixel(&image, map->data[image_getindex(map, it)],
					point_sub(it, start));
		}
		image_put(mlx, &image, (t_point){0, 0});
		const t_point	put = {
			.x = player_map_pos.x - start.x,
			.y = player_map_pos.y - start.y
		};
		if (0 <= player_map_pos.x && player_map_pos.x < map->size.x
			&& 0 <= player_map_pos.y && player_map_pos.y < map->size.y)
		{
			image_put(mlx, player_icon, put);
			cast_a_ray(mlx, put, point_scale(player->dir, 39));
		}
		image_destroy(mlx.p_mlx, &image);
	}
	/* Puts the whole map */
#if 0
	image_put(mlx, map, (t_point){.x = ScreenWidth, .y = ScreenHeight});
	const t_point	offset = {
		.x = ScreenWidth - map->size.x,
		.y = ScreenHeight - map->size.y
	};
	image_put(mlx, player_icon, point_add(offset, player_map_pos));
#endif
}

// ft_printf("くるり廻る廻る廻る世界\n");
int	hook_loop(t_game *game)
{
	if (game->keys[Key_ESC] == Press)
		hook_button_close(EXIT_SUCCESS);
	/* Rotate the player direction, based on the mouse movement and left right keys */
	{
		mlx_mouse_move(game->mlx.p_win, ScreenWidth / 2, ScreenHeight / 2);
		player_rotate(&game->player.dir, game->mouse, game->keys);
		game->mouse.pos = (t_point){.x = ScreenWidth / 2, .y = ScreenHeight / 2};
		game->mouse.prev_pos = (t_point){.x = ScreenWidth / 2, .y = ScreenHeight / 2};
	}
	/* Move the player */
	player_move(&game->player, player_direction(game->keys));
	mlx_clear_window(game->mlx.p_mlx, game->mlx.p_win);
	raycast(game->mlx, &game->screen_buffer, &game->player, game->map);
	/* Background render */
	{
		// put_background(game->mlx);
		// image_put(game->mlx, &game->screen_buffer, (t_point){0, 0});
		/* Minimap */
		{
			put_minimap(game->mlx, &game->texture.map, &game->player, &game->texture.player_icon);
		}
	}
	/* Put the cursor */
	if (display_mouse(game->mouse))
	{
		image_put(game->mlx, &game->texture.mouse_icon, game->mouse.pos);
		// if (game->mouse.left_click == Press)
			// cast_a_ray(game->mlx, game->player.pos, point_sub(game->mouse.pos, game->player.pos));
	}
	return (0);
}

#define FIELD_OF_VIEW	120

int	main(void)
{
	t_game	game;
	t_image	image;

	game = game_init();
	// game.player.pos = point_scale(game.map.size, CELL_SIZE * .50);
	game.player.pos = (t_point){1.50, 1.50};
	game.player.dir = (t_point){.x = 0, .y = -1}; /* N, S, E, W */
	// game.player.plane = game.player.dir;
	game.player.plane = (t_point){1, 0};
	// image_fill(game.screen_buffer, colour_from_rgba(100, 100, 100, 0));
	// image_put(game.mlx, game.screen_buffer, (t_point){0, 0});
	beta_screen_buffer(game.screen_buffer);
	events(&game);
	mlx_loop(game.mlx.p_mlx);
}
