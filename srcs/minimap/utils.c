/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minimap.h"

t_point	map_scale_point(const t_point point)
{
	return (point_upscale(point, MapCellSize + 1));
}

void	map_draw_tile(t_image *map, const t_colour colour, const t_point pos)
{
	const t_point	start = map_scale_point(pos);
	const t_point	img_end = {
		.x = ft_dmin(map->size.x, start.x + MapCellSize),
		.y = ft_dmin(map->size.y, start.y + MapCellSize)
	};
	const t_point	img_start = point_max(start, (t_point){0, 0});

	image_draw_rectangle(map, colour, img_start, img_end);
}
