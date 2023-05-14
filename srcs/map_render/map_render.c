#include "cub3d.h"

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

static void	layers_create(t_map_layers layers, void *p_mlx,
			const t_point size, const t_point putoffset)
{
	unsigned int	i;

	i = -1;
	while (++i < layer_count)
	{
		layers[i] = image_create(p_mlx, size, putoffset);
		ft_assert(layers[i].data != NULL, "layers_create: layers creation failed");
		image_clean(&layers[i]);
	}
}

static void	map_layers_init(t_map_layers layers, const t_game *game)
{
	void *const		p_mlx = game->mlx.p_mlx;
	const t_image	*img_map = &game->texture.map;

	getmap_layers_init(p_mlx, layers, img_map->size, img_map->putoffset);
	map_layers_player(&layers[LayerPlayer], &game->player);
	map_layers_ray(&layers[LayerRay], game->rays, game->player.pos);
	ft_memcpy(layers[LayerMap].data, img_map->data,
		(img_map->size.y * img_map->size.x) * sizeof(t_colour));
}

void	cub3d_map_render(const t_game *game)
{
	t_map_layers	layers;

	map_layers_init(layers, game);
	map_layers_player(&layers[LayerPlayer], &game->player);
	map_layers_ray(&layers[LayerRay], game->rays, game->player.pos);
	put_minimap(game->mlx, layers, layer_count, game->player.pos);
	map_layers_render(game->mlx, layers, layer_count, (t_point){.x = ScreenWidth, .y = ScreenHeight});
	map_layers_destroy(game->mlx.p_mlx, layers, layer_count);
}
