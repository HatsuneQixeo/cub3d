#include "minimap.h"

void	map_layers_destroy(void *p_mlx,
			t_image *arr_layers, const unsigned int length)
{
	unsigned int	i;

	i = -1;
	while(++i < length)
		image_destroy(p_mlx, &arr_layers[i]);
}

void	map_layers_render(t_mlx mlx, const t_image *arr_layers,
			const unsigned int length, const t_point pos)
{
	unsigned int	i;

	i = length;
	while (i--)
		image_put(mlx, &arr_layers[i], pos);
}
