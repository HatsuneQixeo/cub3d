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

int	hook_expose(t_game *game)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(game->mlx.p_win, &x, &y);
	game->mouse.pos = (t_point){.x = x, .y = y};
	game->mouse.prev_pos = game->mouse.pos;
	return (0);
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

/*
	Originally made because a gif conversion seems to have missing pixel.
	My deduction is because certain gif image default into transparent
	if the pixel is the same as the last image,
	probably did so for optimisation purpose?
*/
void	image_copy_opaque(t_image *dst, const t_image *src)
{
	unsigned int	i;

	i = -1;
	while (++i < dst->size.x * dst->size.y)
		if (colour_getmask(src->data[i], ValueA) != 0xff)
			dst->data[i] = src->data[i];
}

void	door_iteri_update(const unsigned int i, void *arr_door)
{
	t_door **const	aa = arr_door;
	t_door *const	door = aa[i];

	if (door->step == 0)
		return ;
	door->animation_index += door->step;
	// door->is_open = (door->animation_index != 0);
	door->is_open = (door->animation_index == door->animation_amount - 1);
	if (door->animation_index == 0
		|| door->animation_index == door->animation_amount - 1)
		door->step = 0;
}

void	render_door(t_game *game);

void	map_update(t_map *map)
{
	t_door	**it_door;

	it_door = map->arr_doors - 1;
	while (*++it_door != NULL)
	{
		const t_point	pos = (*it_door)->pos;

		if ((*it_door)->animation_index != 0)
			map->layout[(int)pos.y][(int)pos.x] = DoorOpen;
		else
			map->layout[(int)pos.y][(int)pos.x] = DoorClose;
	}
}

void	player_interact(const t_map *map, t_keys keys, const t_point target)
{
	t_door	**find;
	t_door	*door;

	if (keys[Key_E] == Release)
		return ;
	keys[Key_E] = Release;
	if (!cubmap_isdoor(map, target))
		return ;
	find = (t_door **)ft_aafind((void **)map->arr_doors, &target, cmp_doorpos);
	ft_assert(find != NULL, "player_interact: Could not find door");
	door = *find;
	if (door->step != 0)
		door->step *= -1;
	else if (door->is_open)
		door->step = -1;
	else
		door->step = 1;
}

void	render_background(t_image *screen_buffer,
			const t_colour ceiling, const t_colour floor)
{
	image_draw_rectangle(screen_buffer, ceiling,
		(t_point){.x = 0, .y = 0},
		(t_point){.x = ScreenWidth, .y = ScreenHeight / 2});
	image_draw_rectangle(screen_buffer, floor,
		(t_point){.x = 0, .y = ScreenHeight / 2},
		(t_point){.x = ScreenWidth, .y = ScreenHeight});
}

// ft_printf("くるり廻る廻る廻る世界\n");
int	hook_loop(t_game *game)
{
	const t_point	screen_center = {
		.x = ScreenWidth / 2,
		.y = ScreenHeight / 2
	};

	TIME("time total",
		if (game->keys[Key_ESC] == Press)
			hook_button_close(EXIT_SUCCESS);
		// mlx_clear_window(game->mlx.p_mlx, game->mlx.p_win);
		/* Update entity like player and door */
		{
			/* Rotate the player direction, based on the mouse movement and left right keys */
			{
				player_rotate(&game->player, game->mouse, game->keys);
				mlx_mouse_move(game->mlx.p_win, screen_center.x, screen_center.y);
				game->mouse.pos = screen_center;
				game->mouse.prev_pos = screen_center;
			}
			player_move(&game->player, player_direction(game->keys), &game->map);
			player_target(&game->player, &game->map);
			player_interact(&game->map, game->keys, game->player.target);
			ft_aaiteri(game->map.arr_doors, door_iteri_update);
			map_update(&game->map);
		}
		render_background(&game->screen_buffer,
			game->texture.colour_ceiling, game->texture.colour_floor);
		/* Raycasting */
		TIME("render total",
			TIME("raycast", screen_rays(game->rays, &game->player, game->map, set_wall()));
			TIME("draw   ", render_wall(&game->screen_buffer, game->rays, game->texture.walls, game->player.pos));
			TIME("put    ", image_put(game->mlx, &game->screen_buffer, (t_point){0, 0}));
			/* put door */
			{
				TIME("raycast", screen_rays(game->rays, &game->player, game->map, set_door()));
				TIME("draw   ", render_door(game));
				TIME("put    ", image_put(game->mlx, &game->screen_buffer, (t_point){0, 0}));
			}
			/* put door */
			{
				TIME("raycast", screen_rays(game->rays, &game->player, game->map, set_any()));
				TIME("draw   ", render_door(game));
				TIME("put    ", image_put(game->mlx, &game->screen_buffer, (t_point){0, 0}));
			}
		);
		/* Minimap */
		// TIME("minimap", cub3d_map_render(game));
		/* Put the temporary cursor */
		if (display_mouse(game->mouse))
			image_put(game->mlx, &game->texture.mouse_icon, game->mouse.pos);
		image_put(game->mlx, &game->texture.mouse_icon, screen_center);
	);
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
	{
		if (!SAN)
			system("leaks -q cub3d");
		exit(1);
	}
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
