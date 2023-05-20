#ifndef MINIMAP_H
# define MINIMAP_H

# include "image.h"
# include "cubmap.h"

enum e_minimap_size
{
	MapCellSize = 32,
	MinimapCell = 7,
	MinimapSize = MapCellSize * MinimapCell
};

void	put_minimap(t_mlx mlx, const t_image *map, t_point player_pos);

t_point	map_scale_point(t_point point);
void	map_draw_tile(t_image *map, t_colour colour, t_point pos);

void	map_layer_layout(t_image *layer, const t_map *map);

#endif
