#include "minimap.h"

static t_point	scale_ray_vector(const t_ray ray)
{
	const double	scaled_distance = ray.distance_traveled * (MapCellSize + 1);
	const t_point	ray_vector = point_upscale(ray.direction, scaled_distance);

	return (ray_vector);
}

void	minimap_layer_ray(t_image *image,
			const t_rays rays, const t_point player_pos)
{
	const t_point	player_map_pos = point_upscale(player_pos, MapCellSize + 1);
	const t_colour	ray_colour = colour_from_rgba(160, 00, 00, 80);
	unsigned int	i;

	if (!point_inbound(player_map_pos, image->size))
		return ;
	i = -1;
	while (++i < ray_amount)
	{
		image_draw_line(image, ray_colour, player_map_pos,
			point_add(player_map_pos, scale_ray_vector(rays[i])));
	}
}

t_point	point_clamp(const t_point point, const t_point min, const t_point max)
{
	const t_point	new_point = {
		.x = ft_dminmax(min.x, point.x, max.x),
		.y = ft_dminmax(min.y, point.y, max.y),
	};

	return (new_point);
}

t_point	point_multiply(const t_point a, const t_point b)
{
	const t_point	point = {
		.x = a.x * b.x,
		.y = a.y * b.y
	};

	return (point);
}

t_point	point_normalize(const t_point point)
{
	const double	magnitude = sqrt(pow(point.x, 2) + pow(point.y, 2));
	const t_point	normalized = point_downscale(point, magnitude);

	return (normalized);
}

static void	layer_player_delta(t_image *image, const t_player *player)
{
	const t_point	map_pos = point_upscale(player->pos, MapCellSize + 1);
	const t_colour	colour = colour_from_percentage(.2, .2, .2, 0);
	t_point	delta = {
		.x = sqrt((1 + pow(player->dir.y, 2) / pow(player->dir.x, 2))),
		.y = sqrt((1 + pow(player->dir.x, 2) / pow(player->dir.y, 2))),
	};
	t_point	end;

	delta = point_upscale(delta, MapCellSize);
	if (player->dir.x == 0)
		delta.x = 0;
	if (player->dir.y == 0)
		delta.y = 0;
	delta = point_multiply(delta, point_sign(player->dir));
	end = point_add(map_pos, delta);
	end = point_clamp(end, (t_point){0, 0},
			(t_point){.x = image->size.x - 1, .y = image->size.y - 1});
	image_draw_line(image, colour, map_pos, end);
}

void	minimap_layer_player(t_image *image, void *p_mlx, const t_player *player)
{
	const t_point	map_pos = point_apply(point_upscale(player->pos, MapCellSize + 1), trunc);

	if (!point_inbound(map_pos, image->size))
		return ;
	layer_player_delta(image, player);
	image_draw_line(image, colour_from_rgba(200, 200, 200, 10),
		map_pos, point_add(map_pos, point_upscale(player->dir, 39)));
}

enum e_layer_index
{
	LayerPlayer,
	LayerRay,
	LayerMap,
	layer_count
};

typedef t_image	t_minimap_layers[layer_count];

/* Should be fine since putoffset will be replaced by t_point offset */
void	minimap_layers_init(t_minimap_layers layers, void *p_mlx,
			const t_point size, t_offset putoffset_x, t_offset putoffset_y)
{
	for (unsigned int i = 0; i < layer_count; i++)
	{
		layers[i] = image_create(p_mlx, size, putoffset_x, putoffset_y);
		ft_assert(layers[i].data != NULL, "minimap_layers_init: layers creation failed");
		image_clean(&layers[i]);
	}
}

void	minimap_layers_destroy(t_minimap_layers layers, void *p_mlx)
{
	for (unsigned int i = 0; i < layer_count; i++)
		image_destroy(p_mlx, &layers[i]);
}

void	minimap_layers_render(t_minimap_layers layers, t_mlx mlx, const t_point pos)
{
	unsigned int	i_put = layer_count;

	while (i_put--)
		image_put(mlx, &layers[i_put], pos);
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

void	minimap_layers_crop(t_minimap_layers layers_cropped,
			const t_minimap_layers layers, void *p_mlx, const t_point pos)
{
	t_point	start;
	t_point	end;

	starttoend(layers[0].size, pos, &start, &end);
	for (unsigned int i = 0; i < layer_count; i++)
	{
		layers_cropped[i] = image_crop(p_mlx, &layers[i], start, end);
		layers_cropped[i].putoffset_x = putoffset_default;
		layers_cropped[i].putoffset_y = putoffset_default;
		ft_assert(layers_cropped[i].data != NULL, "minimap_layers_crop: "IMAGE_CREATION_FAILED);
	}
}

void	put_minimap(t_mlx mlx, const t_image *map_texture, const t_rays rays,
			const t_player *player)
{
	t_minimap_layers	layers;
	const t_point		player_map_pos = point_apply(point_upscale(player->pos, MapCellSize + 1), trunc);

	/* Init */
	{
		minimap_layers_init(layers, mlx.p_mlx, map_texture->size,
			map_texture->putoffset_x, map_texture->putoffset_y);
		minimap_layer_player(&layers[LayerPlayer], mlx.p_mlx, player);
		minimap_layer_ray(&layers[LayerRay], rays, player->pos);
		ft_memcpy(layers[LayerMap].data, map_texture->data,
			(map_texture->size.y * map_texture->size.x) * sizeof(t_colour));
	}
	/* Crop the section around the player out */
	{
		t_minimap_layers	layers_cropped;

		minimap_layers_crop(layers_cropped, layers, mlx.p_mlx, player_map_pos);
		minimap_layers_render(layers_cropped, mlx, (t_point){0, 0});
		minimap_layers_destroy(layers_cropped, mlx.p_mlx);
	}
	/* Put the whole map */
	minimap_layers_render(layers, mlx, (t_point){.x = ScreenWidth, .y = ScreenHeight});
	/* Clear */
	minimap_layers_destroy(layers, mlx.p_mlx);
}

/**
 * @brief Okay, colour_add did not work out,
 * now I have to find alternative for overlapping images.
 * 
 * I suppose the easiest and most straight foward way is to have multiple layers of images,
 * Like:
 * 		A layer of player in map
 * 		A layer of ray in map
 * 		A layer of map layout
 * crop each and every one of them and put them there in the given order
 * 
 * Of course I could just (try to?) do the cropping calculation first,
 * but that approach won't be reflected in the map itself,
 * thus may be redundant to replicate?
 * The calculation itself is a problem to get right already.
 * 
 * 
 * 
 */
