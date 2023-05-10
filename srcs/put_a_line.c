#include "cub3d.h"

static t_offset	offset_vector(const double vector)
{
	if (vector < 0)
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

void	put_a_line(const t_mlx mlx, const t_point pos, const t_point vector)
{
	const t_point	size = (t_point){
		.x = ft_max(fabs(vector.x), 1),
		.y = ft_max(fabs(vector.y), 1)
	};
	t_image			ray;
	t_point			start;
	t_point			end;

	ray = image_create(mlx.p_mlx, size,
			offset_vector(vector.x), offset_vector(vector.y));
	ft_assert(ray.data != NULL, "put_a_line: "IMAGE_CREATION_FAILED);
	start_to_end(&start, &end, size, vector);
	image_clean(&ray);
	image_draw_line(&ray, colour_from_rgba(255, 255, 255, 20), start, end);
	image_put(mlx, &ray, pos);
	image_destroy(mlx.p_mlx, &ray);
}
