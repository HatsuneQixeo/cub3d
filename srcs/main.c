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

// enum e_wall_texture_index	direction_to_face(const t_point direction,
// 			const enum e_side side)
// {
// 	if (side == Horizontal)
// 		return ((enum e_wall_texture_index []){East, West}[direction.x < 0]);
// 	else if (side == Vertical)
// 		return ((enum e_wall_texture_index []){South, North}[direction.y < 0]);
// 	else
// 		ft_assert(0, "direction_to_face: Invalid side");
// 	return (-1);
// }

void	ray_draw_colour(t_image *screen_buffer, t_rays rays)
{
	t_colour		colour;
	unsigned int	i;
	unsigned int	index;
	double			line_height;
	t_point			point_start;
	t_point			point_end;

	i = -1;
	while (++i < ScreenWidth)
	{
		index = i * ((double)ray_amount / ScreenWidth);
		colour = colour_from_rgba(20, 150, 180, 39);
		if (rays[index].distance_traveled == 0)
			colour = 0x393939;
		if (rays[index].side == Vertical)
			colour_setmask(&colour, 39 + 39 + 39, ValueA);
		point_start = (t_point){.x = i, .y = 0};
		point_end = (t_point){.x = i, .y = ScreenHeight};
		if (rays[index].distance_traveled != 0)
		{
			line_height = ScreenHeight / rays[index].distance_traveled;
			point_start.y = ft_max(0, (ScreenHeight - line_height) / 2);
			point_end.y = ft_min(point_end.y, (line_height + ScreenHeight) / 2);
		}
		image_draw_line(screen_buffer, colour, point_start, point_end);
	}
}

/* Scale the plane to the ratio of the screen, ranging between -1 to 1 */
static t_point	scale_plane(const t_point plane, const unsigned int i)
{
	const double	camera_x_ratio = -1 + ((2 * (i + .5)) / ray_amount);
	const t_point	scaled_plane = point_upscale(plane, camera_x_ratio);

	return (scaled_plane);
}

void	screen_rays(t_rays rays, const t_player *player, const t_map map)
{
	const t_point	plane = point_rotate(player->dir, M_PI_2);
	unsigned int	i;

	i = -1;
	while (++i < ray_amount)
		rays[i] = raycast(map.layout, map.size, player->pos,
				point_add(player->dir, scale_plane(plane, i)));
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

t_image	minimap_show_ray(void *p_mlx, const t_image *img_map, const t_rays rays,
			const t_point player_map_pos);
void	put_minimap(t_mlx mlx, const t_image *map, const t_player *player, const t_image *player_icon);
// ft_printf("くるり廻る廻る廻る世界\n");
int	hook_loop(t_game *game)
{
	if (game->keys[Key_ESC] == Press)
		hook_button_close(EXIT_SUCCESS);
	/* Rotate the player direction, based on the mouse movement and left right keys */
	{
		player_rotate(&game->player, game->mouse, game->keys);
		// mlx_mouse_move(game->mlx.p_win, ScreenMidWidth, ScreenMidHeight);
		// game->mouse.pos = (t_point){.x = ScreenMidWidth, .y = ScreenMidHeight};
		// game->mouse.prev_pos = (t_point){.x = ScreenMidWidth, .y = ScreenMidHeight};
	}
	/* Move the player */
	player_move(&game->player, player_direction(game->keys), game->map.layout, game->map.size);
	// point_log("player: ", game->player.pos);
	mlx_clear_window(game->mlx.p_mlx, game->mlx.p_win);
	/* Raycasting */
	{
		PROFILE("raycast: ", screen_rays(game->rays, &game->player, game->map));
		PROFILE("draw: ", ray_draw_colour(&game->screen_buffer, game->rays));
		PROFILE("put:  ", image_put(game->mlx, &game->screen_buffer, (t_point){0, 0}));
		if (!NO_PROFILE)
			printf("\n");
	}
	/* Minimap */
	{
		t_image	raymap;

		raymap = minimap_show_ray(game->mlx.p_mlx, &game->texture.map, game->rays, game->player.pos);
		put_minimap(game->mlx, &raymap, &game->player, &game->texture.player_icon);
		image_destroy(game->mlx.p_mlx, &raymap);
	}
	/* Put the temporary cursor */
	if (display_mouse(game->mouse))
		image_put(game->mlx, &game->texture.mouse_icon, game->mouse.pos);
	image_clean(&game->screen_buffer);
	return (0);
}

int	cub3d(const char *map_path)
{
	t_game	game;

	if (cmp_strsuffix(map_path, ".cub"))
		return (-!!ft_dprintf(2, "Invalid File extension: %s\n", map_path));
	ft_bzero(&game, sizeof(t_game));
	if (game_init(map_path, &game) == -1)
		hook_button_close(1);
		// return (-1);
	// hook_button_close(0);
	events(&game);
	mlx_loop(game.mlx.p_mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (!!ft_putendl_fd("usage: cub3d <map>", 2));
	cub3d(argv[1]);
	if (!SAN)
		system("leaks -q cub3d");
}
