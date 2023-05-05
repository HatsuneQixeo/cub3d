#include "cub3d.h"

/* Doesn't work the way I think because the map is not always rectangular */
void	put_minimap(t_mlx mlx, const t_image *map, const t_player *player, const t_image *player_icon)
{
	const t_point	player_map_pos = point_upscale(player->pos, MapCellSize);

	/* Sectioned Minimap */
	{
		t_image			image;

		image = image_create(mlx.p_mlx, (t_point){MinimapLength, MinimapLength},
				putoffset_default, putoffset_default);
		ft_assert(image.data != NULL, "put_minimap: "IMAGE_CREATION_FAILED);
		image_clean(&image);
		t_point	start = {
			.x = ft_max(0, player_map_pos.x - (image.size.x / 2)),
			.y = ft_max(0, player_map_pos.y - (image.size.y / 2))
		};
		const t_point	end = {
			.x = ft_min(map->size.x, start.x + image.size.x),
			.y = ft_min(map->size.y, start.y + image.size.y)
		};

		if (end.x == map->size.x)
			start.x = ft_max(0, map->size.x - image.size.x);
		if (end.y == map->size.y)
			start.y = ft_max(0, map->size.y - image.size.y);
		t_point	it;
		it.y = start.y - 1;
		while (++it.y < end.y)
		{
			it.x = start.x - 1;
			while (++it.x < end.x)
				image_draw_pixel(&image, map->data[image_getindex(map, it)],
					point_sub(it, start));
		}
		image_put(mlx, &image, (t_point){0, 0});

		{
			const t_point	put = point_sub(player_map_pos, start);

			if (0 <= put.x && put.x < image.size.x
				&& 0 <= put.y && put.y < image.size.y)
			{
				image_put(mlx, player_icon, put);
				draw_a_line(mlx, put, point_upscale(player->dir, 39));
			}
		}
		image_destroy(mlx.p_mlx, &image);
	}
	/* Puts the whole map */
#if 1
	image_put(mlx, map, (t_point){.x = ScreenWidth, .y = ScreenHeight});
	const t_point	offset = {
		.x = ScreenWidth - map->size.x,
		.y = ScreenHeight - map->size.y
	};
	image_put(mlx, player_icon, point_add(offset, player_map_pos));
#endif
}
