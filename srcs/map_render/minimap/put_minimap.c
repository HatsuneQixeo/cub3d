#include "minimap.h"

/* Don't think this works for whatever reason */
// void	image_draw_image(t_image *dst, const t_image *src, const t_point pos)
// {
// 	const t_point	offset = point_apply(src->putoffset, trunc);
// 	const t_point	begin = {
// 		.x = ft_dmax(0, pos.x + offset.x),
// 		.y = ft_dmax(0, pos.x + offset.y)
// 	};
// 	const t_point	end = {
// 		.x = ft_dmin(dst->size.x, pos.x + offset.x + src->size.x),
// 		.y = ft_dmin(dst->size.y, pos.y + offset.y + src->size.y),
// 	};
// 	t_point			it;

// 	if (!(begin.x < end.x && begin.y < end.y))
// 		return ;
// 	it.y = begin.y - 1;
// 	while (++it.y < end.y)
// 	{
// 		it.x = begin.x - 1;
// 		while (++it.x < end.x)
// 			image_setpixel(dst, image_getpixel(src, point_sub(it, offset)), it);
// 	}
// }

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
	const t_point	player_map_pos = point_apply(point_upscale(player_pos, MapCellSize + 1), trunc);
	t_point			start;
	t_point			end;
	t_image			cropped;

	starttoend(map->size, player_map_pos, &start, &end);
	cropped = image_crop(mlx.p_mlx, map, start, end);
	ft_assert(cropped.data != NULL, "put_minimap: "IMAGE_CREATION_FAILED);
	image_put(mlx, &cropped, (t_point){0, 0});
	image_destroy(mlx.p_mlx, &cropped);
}
