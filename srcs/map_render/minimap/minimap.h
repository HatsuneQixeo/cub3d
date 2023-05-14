#ifndef MINIMAP_H
# define MINIMAP_H

# include "image.h"

enum e_minimap_size
{
	MapCellSize = 32,
	MinimapScale = 7,
	MinimapLength = MapCellSize * MinimapScale
};

void	map_layers_destroy(void *p_mlx,
			t_image *arr_layers, unsigned int length);
void	map_layers_render(t_mlx mlx,
			const t_image *arr_layers, unsigned int length, t_point pos);
void	put_minimap(t_mlx mlx, const t_image *arr_layers, unsigned int length,
			t_point player_pos);

#endif
