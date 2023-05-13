#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

enum e_minimap_size
{
	MapCellSize = 32,
	MinimapScale = 7,
	MinimapLength = MapCellSize * MinimapScale
};

void	put_minimap(t_mlx mlx, const t_image *map_texture, const t_rays rays,
			const t_player *player);

#endif
