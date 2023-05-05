#include "ray.h"
#include "libmath.h"

static t_point	side_distance_offset(const t_point pos, const t_point direction,
			const t_point delta_distance)
{
	const t_point	offset = point_sub(pos, point_round(pos, trunc));
	t_point			side_distance;

	if (direction.x < 0)
		side_distance.x = offset.x * delta_distance.x;
	else
		side_distance.x = (1 - offset.x) * delta_distance.x;
	if (direction.y < 0)
		side_distance.y = offset.y * delta_distance.y;
	else
		side_distance.y = (1 - offset.y) * delta_distance.y;
	return (side_distance);
}

int	point_inbound(const t_point point, const t_point size)
{
	return ((0 <= point.x && point.x < size.x)
		&& (0 <= point.y && point.y < size.y));
}

static t_point	go_until_hit(char **map, const t_point mapsize, const t_point pos, t_ray *ray)
{
	const t_point	delta_distance = {
		.x = fabs(1 / ray->direction.x),
		.y = fabs(1 / ray->direction.y)
	};
	const t_point	step = point_sign(ray->direction);
	t_point			side_distance;

	side_distance = side_distance_offset(pos, ray->direction, delta_distance);
	ray->hit = point_round(pos, trunc);
	while (point_inbound(ray->hit, mapsize)
		&& map[(int)ray->hit.y][(int)ray->hit.x] != '1')
	{
		if (side_distance.x < side_distance.y)
		{
			side_distance.x += delta_distance.x;
			ray->hit.x += step.x;
			ray->side = Horizontal;
		}
		else
		{
			side_distance.y += delta_distance.y;
			ray->hit.y += step.y;
			ray->side = Vertical;
		}
	}
	if (!point_inbound(ray->hit, mapsize) || !point_inbound(pos, mapsize))
		return ((t_point){(double)1 / 0, (double)1 / 0});
	return (point_sub(side_distance, delta_distance));
}

t_ray	raycast(char **map, const t_point mapsize,
			const t_point pos, const t_point ray_direction)
{
	t_ray	ray;
	t_point	distance;

	ray.direction = ray_direction;
	distance = go_until_hit(map, mapsize, pos, &ray);
	ray.distance_traveled = ft_dmax(0, ft_dmax(distance.y, distance.x));
	return (ray);
}
