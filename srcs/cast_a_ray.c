#include "cub3d.h"

static t_offset	offset_direction(const double direction)
{
	if (direction > 0)
		return (putoffset_inverted);
	else
		return (putoffset_default);
}

static void	start_to_end(t_point *start, t_point *end,
			const t_point size, const t_point direction)
{
	ft_bzero(start, sizeof(*start));
	*end = size;
	if (direction.x < 0)
	{
		start->x = size.x - 1;
		end->x = -1;
	}
	if (direction.y < 0)
	{
		start->y = size.y - 1;
		end->y = -1;
	}
}

void	cast_a_ray(const t_mlx mlx, const t_point player, const t_point direction)
{
	const t_point	size = (t_point){
		.x = ft_max(fabs(direction.x), 1),
		.y = ft_max(fabs(direction.y), 1)
	};
	const t_image	ray = image_create(mlx.p_mlx, size,
				offset_direction(direction.x), offset_direction(direction.y));
	t_point			start;
	t_point			end;

	ft_assert(ray.data != NULL, "cast_a_ray: Image creation failed");
	start_to_end(&start, &end, size, direction);
	image_clear(ray);
	image_draw_line(ray, colour_from_rgba(255, 120, 100, 20), start, end);
	image_put(mlx, ray, player);
}
