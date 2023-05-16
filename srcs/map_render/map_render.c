#include "cub3d.h"

#ifndef SHOW_RAY
# define SHOW_RAY	0
#endif

void	map_layers_ray(t_image *layer, const t_rays rays, t_point start);
void	map_layers_player(t_image *layer, const t_player *player);

enum e_layer_index
{
	LayerPlayer,
	LayerRay,
	LayerMap,
	layer_count
};

typedef t_image	t_map_layers[layer_count];

static void	map_layers_destroy(void *p_mlx, t_map_layers layers)
{
	unsigned int	i;

	i = -1;
	while (++i < layer_count)
		image_destroy(p_mlx, &layers[i]);
}

/*
	Pos in put_minimap means the player_pos,
	the image is always put at the top left corner.

	Pos in image_put means the position the image will be put at,
	adding the implicit variable of offset in the image.

	It's probably a bad practice to group functions with same parameter
	but takes the value in different context,
	tho the problem is more on put_minimap not asking for enough argument,
	like where the image should be put.

	Why do I still keep it this way, frankly I don't think it matters,
	and it keeps thing simple for not having more files to maintain.
*/
static void	map_layers_render(t_mlx mlx, const t_map_layers layers,
			const t_point pos, void (*put)(t_mlx, const t_map_layers, t_point))
{
	unsigned int	i;

	i = layer_count;
	while (i--)
		put(mlx, &layers[i], pos);
}

static void	layers_create(void *p_mlx, t_map_layers layers,
			const t_point size, const t_point putoffset)
{
	unsigned int	i;

	i = -1;
	while (++i < layer_count)
	{
		layers[i] = image_create(p_mlx, size, putoffset);
		ft_assert(layers[i].data != NULL,
			"layers_create: "IMAGE_CREATION_FAILED);
		image_clean(&layers[i]);
	}
}

void	cub3d_map_render(t_mlx mlx, const t_image *img_map,
			const t_rays rays, const t_player *player)
{
	t_map_layers	layers;
	const t_point	map_pos = point_sub((t_point){
				.x = ScreenWidth,
				.y = ScreenHeight
			}, img_map->size);

	{
		layers_create(mlx.p_mlx, layers, img_map->size, img_map->putoffset);
		map_layers_player(&layers[LayerPlayer], player);
		if (SHOW_RAY)
			map_layers_ray(&layers[LayerRay], rays, player->pos);
		ft_memcpy(layers[LayerMap].data, img_map->data,
			(img_map->size.y * img_map->size.x) * sizeof(t_colour));
	}
	map_layers_render(mlx, layers, player->pos, put_minimap);
	map_layers_render(mlx, layers, map_pos, image_put);
	map_layers_destroy(mlx.p_mlx, layers);
}
