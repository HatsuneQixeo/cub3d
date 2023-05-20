#include "cub3d.h"

#ifndef SHOW_RAY
# define SHOW_RAY	0
#endif

void	map_layer_ray(t_image *layer, const t_rays rays, t_point start);
void	map_layer_player(t_image *layer, const t_player *player);
void	map_layer_door(t_image *layer, t_door **arr_door);
void	map_layer_interact(t_image *layer, const t_player *player);

static void	map_layer_destroy(void *p_mlx, t_map_layers layers)
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

	Why do I still keep it this way? Frankly I don't think it matters,
	and it keeps thing simple for not having more files to maintain.
*/
static void	map_layer_render(t_mlx mlx, const t_map_layers layers,
			const t_point pos, void (*put)(t_mlx, const t_map_layers, t_point))
{
	unsigned int	i;

	i = layer_count;
	while (i--)
		put(mlx, &layers[i], pos);
}

static void	layers_clean(void *p_mlx, t_map_layers layers)
{
	unsigned int	i;

	i = -1;
	while (++i < layer_count)
	{
		if (i == LayerMap)
			continue ;
		// point_log("size", layers[i].size);
		// printf("area: %d\n", (int)(layers[i].size.y * layers[i].size.x));
		image_clean(&layers[i]);
	}
}

/*
	Due to having to clean every layers with size of mapsize * (MapCellSize + 1)
	everytime it renders,
	this function is incredibly slow if the mapsize is very big
*/
void	cub3d_map_render(t_game *game)
{
	t_image *const	layers = game->texture.map_layers;

	{
		TIME("layer clean", layers_clean(game->mlx.p_mlx, layers));
		TIME("layer player", map_layer_player(&layers[LayerPlayer], &game->map.player));
		TIME("layer interact", map_layer_interact(&layers[LayerInteract], &game->map.player));
		if (SHOW_RAY)
			map_layer_ray(&layers[LayerRay], game->rays, game->map.player.pos);
		TIME("layer door", map_layer_door(&layers[LayerDoor], game->map.arr_doors));
	}
	map_layer_render(game->mlx, layers, game->map.player.pos, put_minimap);
}
