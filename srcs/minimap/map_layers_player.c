/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_layers_player.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minimap.h"

// t_point	point_multiply(const t_point a, const t_point b)
// {
// 	const t_point	point = {
// 		.x = a.x * b.x,
// 		.y = a.y * b.y
// 	};

// 	return (point);
// }

// static void	layer_player_delta(t_image *layer, const t_player *player)
// {
// 	const t_point	map_pos = map_scale_point(player->pos);
// 	const t_colour	colour = colour_from_percentage(.2, .2, .2, 0);
// 	t_point			delta;
// 	t_point			end;

// 	delta = (t_point){
// 		.x = sqrt((1 + pow(player->dir.y, 2) / pow(player->dir.x, 2))),
// 		.y = sqrt((1 + pow(player->dir.x, 2) / pow(player->dir.y, 2))),
// 	};
// 	delta = map_scale_point(delta);
// 	if (player->dir.x == 0)
// 		delta.x = 0;
// 	if (player->dir.y == 0)
// 		delta.y = 0;
// 	delta = point_multiply(delta, point_sign(player->dir));
// 	end = point_add(map_pos, delta);
// 	end = point_clamp(end, (t_point){0, 0},
// 			(t_point){.x = layer->size.x - 1, .y = layer->size.y - 1});
// 	image_draw_line(layer, colour, map_pos, end);
// }

void	map_layer_player(t_image *layer, const t_point dir,
			const t_minimapdata data)
{
	const t_colour	colour = colour_from_percentage(.2, .8, .8, .4);

	if (!point_inbound(data.player_pos, layer->size))
		return ;
	image_draw_line(layer, colour_from_rgba(100, 200, 200, 10),
		data.player_pos, point_add(data.player_pos, map_scale_point(dir)));
	image_draw_circle(layer, colour, data.player_pos, 9);
}
