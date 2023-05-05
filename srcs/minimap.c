#include "cub3d.h"

static t_point	scale_ray_vector(const t_ray ray)
{
	const double	scaled_distance = ray.distance_traveled * (MapCellSize + 1);
	const t_point	ray_vector = point_upscale(ray.direction, scaled_distance);

	return (ray_vector);
}

t_image	minimap_show_ray(void *p_mlx, const t_image *img_map, const t_rays rays,
			const t_point player_pos)
{
	const t_point	player_map_pos = point_upscale(player_pos, MapCellSize + 1);
	const t_colour	ray_colour = colour_from_rgba(200, 0, 0, 0);
	t_image			image;
	unsigned int	i;
	unsigned int	index;

	image = image_dup(p_mlx, img_map);
	ft_assert(image.data != NULL, "minimap_show_ray: image creation failed");
	if (!point_inbound(player_map_pos, img_map->size))
		return (image);
	i = -1;
	while (++i < ray_amount)
	{
		index = i * ((double)ray_amount / ScreenWidth);
		image_draw_line(&image, ray_colour, player_map_pos,
			point_add(player_map_pos, scale_ray_vector(rays[index])));
	}
	return (image);
}

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

/* Doesn't work the way I think because the map is not always rectangular */
void	put_minimap(t_mlx mlx, const t_image *img_map, const t_player *player,
			const t_image *player_icon)
{
	const t_point	player_map_pos = point_add(player->pos,
			point_upscale(player->pos, MapCellSize));

	// point_log("scaled map pos: ", player_map_pos);
	{
		/* Sectioned Minimap */
		t_image	image;
		t_point	start;
		t_point	end;
		t_point	it;

		image = image_create(mlx.p_mlx, (t_point){MinimapLength, MinimapLength},
				putoffset_default, putoffset_default);
		ft_assert(image.data != NULL, "put_minimap: "IMAGE_CREATION_FAILED);
		image_clean(&image);
		starttoend(img_map->size, player_map_pos, &start, &end);
		it.y = start.y - 1;
		while (++it.y < end.y)
		{
			it.x = start.x - 1;
			while (++it.x < end.x)
				image_draw_pixel(&image,
					img_map->data[image_getindex(img_map, it)],
					point_sub(it, start));
		}
		image_put(mlx, &image, (t_point){0, 0});

		{
			const t_point	put = point_sub(player_map_pos, start);

			if (point_inbound(put, (t_point){MinimapLength, MinimapLength}))
			{
				image_put(mlx, player_icon, put);
				put_a_line(mlx, put, point_upscale(player->dir, 39));
			}
		}
		image_destroy(mlx.p_mlx, &image);
	}
	/* Puts the whole map */
	if (1)
	{
		image_put(mlx, img_map, (t_point){.x = ScreenWidth, .y = ScreenHeight});
		const t_point	offset = {
			.x = ScreenWidth - img_map->size.x,
			.y = ScreenHeight - img_map->size.y
		};
		image_put(mlx, player_icon, point_add(offset, player_map_pos));
	}
}
