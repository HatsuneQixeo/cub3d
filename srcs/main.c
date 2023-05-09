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

enum e_wall_texture_index	direction_to_face(const t_point direction,
			const enum e_side side)
{
	if (side == Horizontal)
		return ((enum e_wall_texture_index []){East, West}[direction.x > 0]);
	else if (side == Vertical)
		return ((enum e_wall_texture_index []){South, North}[direction.y > 0]);
	else
		ft_assert(0, "direction_to_face: Invalid side");
	return (-1);
}

int	get_image_x(const t_image *image, const t_ray ray, const t_point player_pos)
{
	const t_point	dist = point_upscale(ray.direction, ray.distance_traveled);
	const t_point	hit = point_add(player_pos, dist);
	const t_point	offset = point_sub(hit, point_round(hit, trunc));
	const double	wall_x = (ray.side == Vertical ? offset.x : offset.y);
	const int		image_x = wall_x * image->size.x;

	if ((ray.side == Horizontal && ray.direction.x < 0)
		|| (ray.side == Vertical && ray.direction.y > 0))
		return (image->size.x - image_x - 1);
	else
		return (image_x);
}

static void	draw_line(t_image *screen_buffer, const t_image *image,
			const double line_height, const unsigned int image_x, const unsigned int buffer_x)
{
	const double	image_step = (image->size.y / line_height);
	double			screen_y;
	const double	screen_end_y = ft_dmin(ScreenHeight,
			(line_height + ScreenHeight) / 2);
	double			it_img_y;

	screen_y = ft_dmax(0, (ScreenHeight - line_height) / 2);
	it_img_y = (screen_y + ((line_height - ScreenHeight) / 2)) * image_step;
	screen_y--;
	while (++screen_y < screen_end_y)
	{
		const t_colour	colour = image_getpixel(image, (t_point){.x = image_x, .y = trunc(it_img_y)});

		image_setpixel(screen_buffer, colour, (t_point){.x = buffer_x, .y = screen_y});
		it_img_y += image_step;
	}
}

void	ray_draw_texture(t_image *screen_buffer, const t_rays rays,
			const t_wall_textures walls, const t_point player_pos)
{
	unsigned int	i;

	i = -1;
	while (++i < ScreenWidth)
	{
		const unsigned int	i_ray = i * ((double)ray_amount / ScreenWidth);
		const t_ray			ray = rays[i_ray];
		const t_image		*image = &walls[direction_to_face(ray.direction, ray.side)];
		const double		line_height = ScreenHeight / ray.distance_traveled;
		const int			image_x = get_image_x(image, ray, player_pos);

		draw_line(screen_buffer, image, line_height, image_x, i);
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
	static int	custom_cursor;
	const int	in_screen = (unsigned int)mouse.pos.x < ScreenWidth
		&& (unsigned int)mouse.pos.y < ScreenHeight;

	if (in_screen != custom_cursor)
	{
		custom_cursor = in_screen;
		(int (*[])(void)){mlx_mouse_show, mlx_mouse_hide}[custom_cursor]();
	}
	return (custom_cursor);
}

void	image_copy_opaque(t_image *dst, const t_image *src)
{
	unsigned int	i;

	i = -1;
	while (++i < dst->size.x * dst->size.y)
		if (colour_getmask(src->data[i], ValueA) != 255)
			dst->data[i] = src->data[i];
}

t_image	minimap_show_ray(void *p_mlx, const t_image *img_map, const t_rays rays,
			const t_point player_map_pos);
void	put_minimap(t_mlx mlx, const t_image *map, const t_player *player, const t_image *player_icon);
// ft_printf("くるり廻る廻る廻る世界\n");
int	hook_loop(t_game *game)
{
	if (game->keys[Key_ESC] == Press)
		hook_button_close(EXIT_SUCCESS);
	image_draw_rectangle(&game->screen_buffer, game->texture.colour_ceiling,
		(t_point){.x = 0, .y = 0},
		(t_point){.x = ScreenWidth, .y = ScreenMidHeight});
	image_draw_rectangle(&game->screen_buffer, game->texture.colour_floor,
		(t_point){.x = 0, .y = ScreenMidHeight},
		(t_point){.x = ScreenWidth, .y = ScreenHeight});
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
		// PROFILE("draw: ", ray_draw_colour(&game->screen_buffer, game->rays));
		PROFILE("draw: ", ray_draw_texture(&game->screen_buffer, game->rays, game->texture.walls, game->player.pos));
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
