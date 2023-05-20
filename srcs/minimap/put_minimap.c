#include "minimap.h"

static void	starttoend(const t_point img_mapsize, const t_point player_map_pos,
			t_point *start, t_point *end)
{
	*start = (t_point){
		.x = ft_max(0, player_map_pos.x - (MinimapSize / 2)),
		.y = ft_max(0, player_map_pos.y - (MinimapSize / 2))
	};
	*end = (t_point){
		.x = ft_min(img_mapsize.x, start->x + MinimapSize),
		.y = ft_min(img_mapsize.y, start->y + MinimapSize)
	};
	if (end->x == img_mapsize.x)
		start->x = ft_max(0, img_mapsize.x - MinimapSize);
	if (end->y == img_mapsize.y)
		start->y = ft_max(0, img_mapsize.y - MinimapSize);
}

void	put_minimap(t_mlx mlx, const t_image *map, const t_point player_pos)
{
	t_point	start;
	t_point	end;
	t_image	cropped;

	starttoend(map->size, point_apply(map_scale_point(player_pos), trunc),
		&start, &end);
	cropped = image_crop(mlx.p_mlx, map, start, end);
	if (!image_good(&cropped))
		return ;
	image_put(mlx, &cropped, (t_point){0, 0});
	image_destroy(mlx.p_mlx, &cropped);
}
