#include "cub3d.h"

void	map_draw_tile(t_image *map, t_colour colour, t_point pos);

void	map_layer_door(t_image *layer, t_door **arr_door)
{
	t_colour		colour;
	unsigned int	i;

	i = -1;
	while (arr_door[++i] != NULL)
	{
		colour = colour_from_percentage(.2, .8, .2, .5);
		if (arr_door[i]->is_open)
			colour_setmask(&colour, 0.85 * 255, ValueA);
		map_draw_tile(layer, colour, arr_door[i]->pos);
	}
}
