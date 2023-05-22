#include "minimap.h"

void	map_layer_interact(t_image *layer, const t_point target,
			const t_minimapdata data)
{
	const t_colour	colour = colour_from_rgba(0, 255, 255, 3.9 * 39);
	const t_point	pos = point_sub(map_scale_point(target), data.begin);

	if (!point_inbound(pos, layer->size))
		return ;
	map_draw_tile(layer, colour, point_downscale(pos, MapCellSize + 1));
}
