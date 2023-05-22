/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_layers_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minimap.h"
#include "cub3d.h"

static t_point	scale_ray_vector(const t_ray ray)
{
	const double	scaled_distance = ray.magnitude * (MapCellSize + 1);
	const t_point	ray_vector = point_upscale(ray.direction, scaled_distance);

	return (ray_vector);
}

/**
 * @brief 
 * 
 * const t_point	end = point_apply(point_minmax((t_point){-1, -1},
 * 		point_add(data.player_pos, vector),
 * 		layer->size), trunc);
 * 
 * @note This way of clamping ruins the ray proprotion,
 * in other word ruins the visualisation presentation.
 * I suppose I could try to downscale the ray
 *  by the given proportion that went out of bound,
 * but I ain't gonna spent my time debug it if something went wrong.
 * Instead, just turn on the out of bound check and disable the draw warning
 */
void	map_layer_ray(t_image *layer, const t_rays rays,
			const t_minimapdata data)
{
	const t_colour	ray_colour = colour_from_rgba(160, 00, 00, 80);
	unsigned int	i;
	t_point			prev;
	t_point			end;

	if (!point_inbound(data.player_pos, layer->size))
		return ;
	prev = (t_point){0, 0};
	i = -1;
	while (++i < ray_amount)
	{
		end = point_add(data.player_pos, scale_ray_vector(rays[i]));
		if (end.x == prev.x && end.y == prev.y)
			continue ;
		image_draw_line(layer, ray_colour, data.player_pos, end);
		prev = end;
	}
}
