/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/* Scale the plane to the ratio of the screen, ranging between -1 to 1 */
static t_point	scale_plane(const t_point plane, const unsigned int i)
{
	const double	camera_x_ratio = -1 + ((2 * (i + .5)) / ray_amount);
	const t_point	scaled_plane = point_upscale(plane, camera_x_ratio);

	return (scaled_plane);
}

void	screen_rays(t_rays rays, const t_map *map, const char *target)
{
	const t_point	plane = point_rotate(map->player.dir, M_PI_2);
	unsigned int	i;

	i = -1;
	while (++i < ray_amount)
		rays[i] = raycast(map, map->player.pos,
				point_add(map->player.dir, scale_plane(plane, i)), target);
}
