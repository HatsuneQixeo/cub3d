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
#include "minimap.h"

t_point	minimap_scale_point(const t_point point)
{
	return (point_upscale(point, MapCellSize + 1));
}

void	cub3d_runtime_assertion(const int condition, const char *attachment)
{
	if (condition)
		return ;
	ft_putendl_fd("Error", 2);
	perror(attachment);
	exit(1);
}

void	map_draw_tile(t_image *map, const t_colour colour, const t_point pos)
{
	const t_point	map_start = point_upscale(pos, MapCellSize + 1);
	const t_point	map_end = point_add(map_start,
			(t_point){MapCellSize, MapCellSize});

	image_draw_rectangle(map, colour, map_start, map_end);
}

void	layer_map(t_image *layer, const t_map map)
{
	const t_colour	wall_colour = colour_from_percentage(.70, .90, .90, .70);
	const t_colour	space_colour = colour_from_percentage(.20, .30, .40, .70);
	t_point			it;

	image_fill(layer, colour_from_percentage(.0, .20, .20, .50));
	it.y = -1;
	while (++it.y < map.size.y)
	{
		it.x = -1;
		while (++it.x < map.size.x)
		{
			if (map.layout[(int)it.y][(int)it.x] == Wall)
				map_draw_tile(layer, wall_colour, it);
			else
				map_draw_tile(layer, space_colour, it);
		}
	}
}

void	image_setalpha(t_image *image, const t_colour_byte value)
{
	unsigned int		i;
	const unsigned int	len = image->size.y * image->size.x;

	i = -1;
	while (++i < len)
		colour_setmask(&image->data[i], value, ValueA);
}

static t_image	*texture_init_door(void *p_mlx, unsigned int *len)
{
	const char *const	filename = "sprites/weekender-girl-heart.xgif";
	char **const		strlist = ft_readfile(filename);
	t_image				*animation;

	cub3d_runtime_assertion(strlist != NULL, filename);
	*len = ft_strcount(strlist);
	animation = malloc(sizeof(*animation) * (*len));
	if (animation == NULL)
		return (NULL);
	for (unsigned int i = 0; i < *len; i++)
	{
		animation[i] = image_readxpm(p_mlx, strlist[i],
				putoffset_default, putoffset_default);
		cub3d_runtime_assertion(image_good(&animation[i]), strlist[i]);
		image_setalpha(&animation[i], ft_min(0xff * ((double)i / *len), 0xbf));
	}
	ft_strlistclear(strlist);
	return (animation);
}

static void	texture_init_map(void *p_mlx, t_map_layers layers, const t_map map)
{
	unsigned int	i;
	const t_point	size = point_sub(point_upscale(map.size, MapCellSize + 1),
			(t_point){1, 1});
	const t_point	putoffset = {0, 0};

	i = -1;
	while (++i < layer_count)
	{
		layers[i] = image_create(p_mlx, size, putoffset);
		cub3d_runtime_assertion(image_good(&layers[i]), "texture_init_map");
	}
	layer_map(&layers[LayerMap], map);
}

static void	texture_init(void *p_mlx, t_texture *texture, const t_map map)
{
	{
		texture->mouse_icon = image_readxpm(p_mlx, "sprites/Normal-Select.xpm",
				putoffset_default, putoffset_default);
		cub3d_runtime_assertion(image_good(&texture->mouse_icon),
			"mouse_icon creation");
	}
	{
		texture_init_map(p_mlx, texture->map_layers, map);
	}
	{
		texture->walls[Invalid] = image_create(p_mlx, (t_point){1, 1}, (t_point){0, 0});
		cub3d_runtime_assertion(image_good(&texture->walls[Invalid]),
			"invalid side of wall creation");
		texture->walls[Invalid].data[0] = 0x00000000;
	}
	{
		texture->door_animation = texture_init_door(p_mlx, &texture->door_animation_len);
		cub3d_runtime_assertion(texture->door_animation != NULL, "init_door");
	}
}

/* Initialization and assertion */
int	game_init(const char *path, t_game *game)
{
	game->mlx.p_mlx = mlx_init();
	cub3d_runtime_assertion(game->mlx.p_mlx != NULL, "mlx_init");
	if (cubmap_getmap(game->mlx.p_mlx, path, &game->map, &game->texture) == -1
		|| cubmap_player_init(game->map, &game->player) == -1)
		return (-1);
	texture_init(game->mlx.p_mlx, &game->texture, game->map);
	cubmap_door_init(&game->map, game->texture.door_animation_len);
	game->screen_buffer = image_create(game->mlx.p_mlx,
			(t_point){.x = ScreenWidth, .y = ScreenHeight},
			(t_point){0, 0});
	cub3d_runtime_assertion(image_good(&game->screen_buffer),
		"screen_buffer creation");
	ft_intset((int *)game->keys, key_count, Release);
	game->mouse.left_click = Release;
	game->mlx.p_win = mlx_new_window(game->mlx.p_mlx, ScreenWidth, ScreenHeight,
			"cub3d");
	cub3d_runtime_assertion(game->mlx.p_win != NULL, "mlx_new_window");
	return (0);
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
	// for (int i = 2; i <= 36; i++)
		// ft_mlx_hook(mlx.p_win, i, hook_log, NULL);
	ft_mlx_hook(mlx.p_win, DestroyNotify, hook_button_close, EXIT_SUCCESS);
	ft_mlx_hook(mlx.p_win, KeyPress, hook_key_press, game->keys);
	ft_mlx_hook(mlx.p_win, KeyRelease, hook_key_release, game->keys);
	ft_mlx_hook(mlx.p_win, ButtonPress, hook_mouse_click, &game->mouse);
	ft_mlx_hook(mlx.p_win, ButtonRelease, hook_mouse_release, &game->mouse);
	ft_mlx_hook(mlx.p_win, Expose, hook_expose, game);
	ft_mlx_hook(mlx.p_win, MotionNotify, hook_mouse_move, &game->mouse.pos);
	/* Gotta have to dig into this */
	// mlx_do_sync(mlx.p_mlx);
	mlx_loop_hook(mlx.p_mlx, hook_loop, game);
}
