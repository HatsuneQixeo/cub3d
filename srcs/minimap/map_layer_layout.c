#include "minimap.h"

void	map_layer_layout(t_image *layer, const t_map *map)
{
	const t_colour	wall_colour = colour_from_percentage(.70, .90, .90, .70);
	const t_colour	space_colour = colour_from_percentage(.20, .30, .40, .70);
	t_point			it;

	image_fill(layer, colour_from_percentage(.0, .20, .20, .50));
	it.y = -1;
	while (++it.y < map->size.y)
	{
		it.x = -1;
		while (++it.x < map->size.x)
		{
			if (map->layout[(int)it.y][(int)it.x] == Wall)
				map_draw_tile(layer, wall_colour, it);
			else
				map_draw_tile(layer, space_colour, it);
		}
	}
}
