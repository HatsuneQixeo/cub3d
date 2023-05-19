#include "cub3d.h"

void	map_draw_tile(t_image *map, t_colour colour, t_point pos);

void	map_layer_interact(t_image *layer, const t_player *player)
{
	const t_colour	colour = colour_from_rgba(0, 255, 255, 3.9 * 39);

	map_draw_tile(layer, colour, player->target);
}
