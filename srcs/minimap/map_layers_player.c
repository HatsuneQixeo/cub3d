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

void	map_layer_player(t_image *layer, const t_point dir,
			const t_minimapdata data)
{
	const t_colour	colour = colour_from_percentage(.2, .8, .8, .4);

	if (!point_inbound(data.player_pos, layer->size))
		return ;
	image_draw_line(layer, colour_from_rgba(100, 200, 200, 10),
		data.player_pos, point_add(data.player_pos, map_scale_point(dir)));
	image_draw_filled_circle(layer, colour, data.player_pos, 9);
}
