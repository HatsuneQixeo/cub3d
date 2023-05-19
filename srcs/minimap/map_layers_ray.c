#include "minimap.h"
#include "cub3d.h"

static t_point	scale_ray_vector(const t_ray ray)
{
	const double	scaled_distance = ray.distance_traveled * (MapCellSize + 1);
	const t_point	ray_vector = point_upscale(ray.direction, scaled_distance);

	return (ray_vector);
}

void	map_layer_ray(t_image *layer,
			const t_rays rays, const t_point player_pos)
{
	const t_point	player_map_pos = map_scale_point(player_pos);
	const t_colour	ray_colour = colour_from_rgba(160, 00, 00, 80);
	unsigned int	i;

	if (!point_inbound(player_map_pos, layer->size))
		return ;
	i = -1;
	while (++i < ray_amount)
	{
		image_draw_line(layer, ray_colour, player_map_pos,
			point_add(player_map_pos, scale_ray_vector(rays[i])));
	}
}
