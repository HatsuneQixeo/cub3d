/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_layers_door.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	map_layer_door(t_image *layer, t_door **arr_door,
			const t_minimapdata data)
{
	t_colour		colour;
	unsigned int	i;

	i = -1;
	while (arr_door[++i] != NULL)
	{
		colour = colour_from_percentage(.2, .8, .2, .5);
		if (arr_door[i]->is_open)
			colour_setmask(&colour, 0.85 * 0xff, ValueA);
		map_draw_tile(layer, colour, point_sub(arr_door[i]->pos,
				point_downscale(data.begin, MapCellSize + 1)));
	}
}
