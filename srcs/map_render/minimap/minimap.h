#ifndef MINIMAP_H
# define MINIMAP_H

# include "image.h"

enum e_minimap_size
{
	MapCellSize = 32,
	MinimapCell = 7,
	MinimapSize = MapCellSize * MinimapCell
};

void	put_minimap(t_mlx mlx, const t_image *map, t_point player_pos);

#endif
