/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void	render_background(t_image *screen_buffer,
			const t_colour ceiling, const t_colour floor)
{
	const unsigned int	len = screen_buffer->size.y * screen_buffer->size.x;
	const unsigned int	half = len / 2;

	ft_intset((int *)screen_buffer->data, half, ceiling);
	ft_intset((int *)screen_buffer->data + half, half + (len & 0b1), floor);
}

typedef void	(*t_ftrender)(t_image *screen_buffer, const t_rays rays,
			const t_image *images, const t_map *map);

static void	render_core(const t_ftrender ft_render, t_game *game,
			const t_image *images, const char *target)
{
	screen_rays(game->rays, &game->map, target);
	ft_render(&game->screen_buffer, game->rays, images, &game->map);
	image_put(game->mlx, &game->screen_buffer, (t_point){0, 0});
}

void	render(t_game *game)
{
	render_background(&game->screen_buffer,
		game->texture.colour_ceiling, game->texture.colour_floor);
	render_core(render_wall, game, game->texture.walls, set_wall());
	render_core(render_door, game, game->texture.door_animation, set_door());
	render_core(render_door, game, game->texture.door_animation, set_any());
}
