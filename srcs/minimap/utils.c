#include "minimap.h"

t_point	map_scale_point(const t_point point)
{
	return (point_upscale(point, MapCellSize + 1));
}

void	map_draw_tile(t_image *map, const t_colour colour, const t_point pos)
{
	const t_point	map_start = map_scale_point(pos);
	const t_point	map_end = point_add(map_start,
			(t_point){MapCellSize, MapCellSize});

	image_draw_rectangle(map, colour, map_start, map_end);
}
