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
#include "minimap.h"

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
	if the pixel is the same as the last image,
	probably for optimisation purpose?
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

void	minimap_layer_interact(t_image *img_map, const t_player *player)
{
	const t_point	pos = point_add(player->pos, player->dir);
	const t_point	rounded = point_apply(pos, trunc);

	point_log("pos: ", pos);
	point_log("rounded: ", rounded);
	printf("\n");
	map_draw_tile(img_map, colour_from_rgba(0, 255, 0, 0), rounded);
}

// ft_printf("くるり廻る廻る廻る世界\n");
int	hook_loop(t_game *game)
{
	const t_point	screen_center = {
		.x = ScreenWidth / 2,
		.y = ScreenHeight / 2
	};

	if (game->keys[Key_ESC] == Press)
		hook_button_close(EXIT_SUCCESS);
	mlx_clear_window(game->mlx.p_mlx, game->mlx.p_win);
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
	/* Raycasting */
	{
		TIME("raycast   ", screen_rays(game->rays, &game->player, game->map));
		TIME("draw      ", ray_draw_texture(&game->screen_buffer, game->rays, game->texture.walls, game->player.pos));
		TIME("put       ", image_put(game->mlx, &game->screen_buffer, (t_point){0, 0}));
	}
	/* Minimap */
	TIME("render map", cub3d_map_render(game));
	/* Put the temporary cursor */
	if (display_mouse(game->mouse))
		image_put(game->mlx, &game->texture.mouse_icon, game->mouse.pos);
	image_put(game->mlx, &game->texture.mouse_icon, screen_center);
	if (BENCHMARK)
		printf("\n");
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
