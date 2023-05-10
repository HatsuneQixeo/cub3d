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

/*
	Originally made because a gif conversion seems to have missing pixel.
	My deduction is because certain gif image default into transparent
	if the pixel is the same as the last image
*/
void	image_copy_opaque(t_image *dst, const t_image *src)
{
	unsigned int	i;

	i = -1;
	while (++i < dst->size.x * dst->size.y)
		if (colour_getmask(src->data[i], ValueA) != 255)
			dst->data[i] = src->data[i];
}

void	map_draw_tile(t_image *map, const t_colour colour, const t_point pos);

void	minimap_show_interact(t_image *img_map, const t_player *player)
{
	const t_point	pos = point_add(player->pos, player->dir);
	const t_point	rounded = point_round(pos, trunc);

	point_log("pos: ", pos);
	point_log("rounded: ", rounded);
	printf("\n");
	map_draw_tile(img_map, colour_from_rgba(0, 255, 0, 0), rounded);
}

void	minimap_draw_player_delta(t_image *img_map, const t_player *player)
{
	const t_point	delta = {
		.x = 1 / player->dir.x,
		.y = 1 / player->dir.y
	};
	const t_point	player_map_pos = point_upscale(player->pos, MapCellSize + 1);

	image_draw_line(img_map, colour_from_percentage(.2, .2, .2, 0),
		player_map_pos, point_add(player_map_pos, point_upscale(delta, MapCellSize)));
}

void	minimap_show_ray(t_image *img_map, const t_rays rays,
			const t_point player_map_pos);
void	put_minimap(t_mlx mlx, const t_image *map, const t_player *player, const t_image *player_icon);
// ft_printf("くるり廻る廻る廻る世界\n");
int	hook_loop(t_game *game)
{
	const t_point	screen_center = {
		.x = ScreenWidth / 2,
		.y = ScreenHeight / 2
	};

	if (game->keys[Key_ESC] == Press)
		hook_button_close(EXIT_SUCCESS);
	image_draw_rectangle(&game->screen_buffer, game->texture.colour_ceiling,
		(t_point){.x = 0, .y = 0},
		(t_point){.x = ScreenWidth, .y = screen_center.y});
	image_draw_rectangle(&game->screen_buffer, game->texture.colour_floor,
		(t_point){.x = 0, .y = screen_center.y},
		(t_point){.x = ScreenWidth, .y = ScreenHeight});
	/* Rotate the player direction, based on the mouse movement and left right keys */
	{
		player_rotate(&game->player, game->mouse, game->keys);
		// mlx_mouse_move(game->mlx.p_win, screen_center.x, screen_center.y);
		// game->mouse.pos = screen_center;
		// game->mouse.prev_pos = screen_center;
	}
	/* Move the player */
	player_move(&game->player, player_direction(game->keys), game->map.layout, game->map.size);
	mlx_clear_window(game->mlx.p_mlx, game->mlx.p_win);
	/* Raycasting */
	{
		PROFILE("raycast: ", screen_rays(game->rays, &game->player, game->map));
		PROFILE("draw: ", ray_draw_texture(&game->screen_buffer, game->rays, game->texture.walls, game->player.pos));
		PROFILE("put:  ", image_put(game->mlx, &game->screen_buffer, (t_point){0, 0}));
		if (!NO_PROFILE)
			printf("\n");
	}
	/* Minimap */
	{
		t_image	raymap;

		raymap = image_dup(game->mlx.p_mlx, &game->texture.map);
		ft_assert(raymap.data != NULL, "raymap image creation failed");
		minimap_show_ray(&raymap, game->rays, game->player.pos);
		// minimap_draw_player_delta(&raymap, &game->player);
		// minimap_show_interact(&raymap, &game->player);
		put_minimap(game->mlx, &raymap, &game->player, &game->texture.player_icon);
		image_destroy(game->mlx.p_mlx, &raymap);
	}
	/* Put the temporary cursor */
	if (display_mouse(game->mouse))
		image_put(game->mlx, &game->texture.mouse_icon, game->mouse.pos);
	image_put(game->mlx, &game->texture.mouse_icon, screen_center);
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
