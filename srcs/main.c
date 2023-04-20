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

void	put_minimap(t_mlx mlx, const t_image *minimap, const t_player *player, const t_image *player_icon)
{
	const t_point	size = (t_point){MinimapLength, MinimapLength};
	t_image			image;
	const t_point	player_pos = point_unscale(player->pos, (double)CELL_SIZE / MinimapCellSize);

	image = image_create(mlx.p_mlx, size, putoffset_default, putoffset_default);
	image_draw_rectangle(&image, colour_from_rgba(20, 150, 200, 50),
		(t_point){0, 0}, image.size);
	t_point	start = {
		.x = ft_max(0, player_pos.x - (size.x / 2)),
		.y = ft_max(0, player_pos.y - (size.y / 2))
	};
	t_point	end = {
		.x = ft_min(minimap->size.x, player_pos.x + (size.x / 2)),
		.y = ft_min(minimap->size.y, player_pos.y + (size.y / 2))
	};
	t_point	it;

	if (start.x == 0)
		end.x = ft_min(minimap->size.x, size.x);
	else if (end.x - start.x < size.x)
		start.x = ft_max(0, minimap->size.x - size.x);
	if (start.y == 0)
		end.y = ft_min(minimap->size.y, size.y);
	else if (end.y - start.y < size.y)
		start.y = ft_max(0, minimap->size.y - size.y);
	it.y = start.y - 1;
	while (++it.y < end.y)
	{
		it.x = start.x - 1;
		while (++it.x < end.x)
			image_draw_pixel(&image, minimap->data[image_getindex(minimap, it)],
				point_sub(it, start));
	}
	image_put(mlx, &image, (t_point){0, 0});
	image_destroy(mlx.p_mlx, &image);
	if (0 < player_pos.x && player_pos.x < size.x
		&& 0 < player_pos.y && player_pos.y < size.y)
		image_put(mlx, player_icon, player_pos);
}

// ft_printf("くるり廻る廻る廻る世界\n");
int	hook_loop(t_game *game)
{
	if (game->keys[Key_ESC] == Press)
		hook_button_close(EXIT_SUCCESS);
	/* Background render */
	{
		mlx_clear_window(game->mlx.p_mlx, game->mlx.p_win);
		put_background(game->mlx);
		image_put(game->mlx, &game->screen_buffer, (t_point){0, 0});
		/* Minimap */
		{
			put_minimap(game->mlx, &game->texture.minimap, &game->player, &game->texture.player_icon);
		}
	}
	/* Rotate the player direction */
	{
		player_rotate(&game->player.dir, game->mouse, game->keys);
		game->mouse.prev_pos = game->mouse.pos;
	}
	/* Move the player */
	{
		player_move(&game->player, player_direction(game->keys));
		image_put(game->mlx, &game->texture.player_icon, game->player.pos);
	}
	/* Render the ray */
	cast_a_ray(game->mlx, game->player.pos, point_scale(game->player.dir, 831 / 2));
	/* Put the cursor */
	if (display_mouse(game->mouse))
	{
		image_put(game->mlx, &game->texture.mouse_icon, game->mouse.pos);
		if (game->mouse.left_click == Press)
			cast_a_ray(game->mlx, game->player.pos, point_sub(game->mouse.pos, game->player.pos));
	}
	return (0);
}

int	main(void)
{
	t_game	game;
	t_image	image;

	game = game_init();
	game.player.pos = point_scale((t_point){
			.x = game.map.size.x,
			.y = game.map.size.y
		}, CELL_SIZE / 2);
	game.player.dir = (t_point){.x = 0, .y = -1}; /* N, S, E, W */
	// image_fill(game.screen_buffer, colour_from_rgba(100, 100, 100, 0));
	// image_put(game.mlx, game.screen_buffer, (t_point){0, 0});
	beta_screen_buffer(game.screen_buffer);
	events(&game);
	mlx_loop(game.mlx.p_mlx);
}
