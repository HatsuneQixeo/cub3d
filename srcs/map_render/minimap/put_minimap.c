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
		.x = ft_max(0, player_map_pos.x - (MinimapLength / 2)),
		.y = ft_max(0, player_map_pos.y - (MinimapLength / 2))
	};
	*end = (t_point){
		.x = ft_min(img_mapsize.x, start->x + MinimapLength),
		.y = ft_min(img_mapsize.y, start->y + MinimapLength)
	};
	if (end->x == img_mapsize.x)
		start->x = ft_max(0, img_mapsize.x - MinimapLength);
	if (end->y == img_mapsize.y)
		start->y = ft_max(0, img_mapsize.y - MinimapLength);
}

static t_image	*crop_minimap(const t_image *arr_layers,
			const unsigned int length, void *p_mlx, const t_point pos)
{
	t_image			*layers_cropped;
	t_point			start;
	t_point			end;
	unsigned int	i;

	starttoend(arr_layers[0].size, pos, &start, &end);
	layers_cropped = malloc(sizeof(t_image) * length);
	if (layers_cropped == NULL)
		return (NULL);
	i = -1;
	while (++i < length)
	{
		layers_cropped[i] = image_crop(p_mlx, &arr_layers[i], start, end);
		ft_assert(layers_cropped[i].data != NULL, "crop_minimap: "IMAGE_CREATION_FAILED);
	}
	return (layers_cropped);
}

void	put_minimap(t_mlx mlx, const t_image *arr_layers,
			const unsigned int length, const t_point player_pos)
{
	const t_point	player_map_pos = point_apply(point_upscale(player_pos, MapCellSize + 1), trunc);
	t_image			*layers_cropped;

	layers_cropped = crop_minimap(arr_layers, length, mlx.p_mlx, player_map_pos);
	map_layers_render(mlx, layers_cropped, length, (t_point){0, 0});
	map_layers_destroy(mlx.p_mlx, layers_cropped, length);
	free(layers_cropped);
}
