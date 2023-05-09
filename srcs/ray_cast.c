#include "cub3d.h"

/* Scale the plane to the ratio of the screen, ranging between -1 to 1 */
static t_point	scale_plane(const t_point plane, const unsigned int i)
{
	const double	camera_x_ratio = -1 + ((2 * (i + .5)) / ray_amount);
	const t_point	scaled_plane = point_upscale(plane, camera_x_ratio);

	return (scaled_plane);
}

void	screen_rays(t_rays rays, const t_player *player, const t_map map)
{
	const t_point	plane = point_rotate(player->dir, M_PI_2);
	unsigned int	i;

	i = -1;
	while (++i < ray_amount)
		rays[i] = raycast(map.layout, map.size, player->pos,
				point_add(player->dir, scale_plane(plane, i)));
}
