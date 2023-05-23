/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

#ifndef SHOW_RAY
# define SHOW_RAY	0
#endif

void	map_layer_ray(t_image *layer, const t_rays rays, t_minimapdata data);

static t_minimapdata	getminimapdata(const t_point img_mapsize,
			const t_point player_pos)
{
	const t_point	player_map_pos = point_apply(
			map_scale_point(player_pos), trunc);
	t_minimapdata	data;

	data.begin = (t_point){
		.x = ft_max(0, player_map_pos.x - (MinimapSize / 2)),
		.y = ft_max(0, player_map_pos.y - (MinimapSize / 2))
	};
	data.end = (t_point){
		.x = ft_min(img_mapsize.x, data.begin.x + MinimapSize),
		.y = ft_min(img_mapsize.y, data.begin.y + MinimapSize)
	};
	if (data.end.x == img_mapsize.x)
		data.begin.x = ft_max(0, img_mapsize.x - MinimapSize);
	if (data.end.y == img_mapsize.y)
		data.begin.y = ft_max(0, img_mapsize.y - MinimapSize);
	data.player_pos = point_apply(point_sub(player_map_pos, data.begin), trunc);
	return (data);
}

static void	map_layers_render(t_mlx mlx, const t_map_layers layers)
{
	unsigned int	i;

	i = layer_count;
	while (i--)
		image_put(mlx, &layers[i], (t_point){0, 0});
}

/*
	Excluding the map layer is something that came to mind
	 for a little bit of optimisation,
	but there would be black frame
	 if the minimap is larger than the actual map size
*/
static void	map_layers_init(void *p_mlx, t_map_layers layers)
{
	unsigned int	i;
	const t_point	size = {MinimapSize, MinimapSize};

	i = -1;
	while (++i < layer_count)
	{
		if (!image_good(&layers[i]))
		{
			layers[i] = image_create(p_mlx, size, (t_point){0, 0});
			cub3d_runtime_assertion(image_good(&layers[i]), "layers_init");
		}
		image_clean(&layers[i]);
	}
}

static void	map_layer_map(t_image *layer, const t_image *img_map,
			const t_minimapdata data)
{
	t_point	it;

	it.y = data.begin.y - 1;
	while (++it.y < data.end.y)
	{
		it.x = data.begin.x - 1;
		while (++it.x < data.end.x)
			image_setpixel(layer, image_getpixel(img_map, it),
				point_sub(it, data.begin));
	}
}

void	cub3d_map_render(t_game *game)
{
	static t_map_layers	layers;
	const t_minimapdata	data = getminimapdata(game->texture.map.size,
			game->map.player.pos);

	map_layers_init(game->mlx.p_mlx, layers);
	map_layer_player(&layers[LayerPlayer], game->map.player.dir, data);
	map_layer_interact(&layers[LayerInteract], game->map.player.target, data);
	if (SHOW_RAY)
		map_layer_ray(&layers[LayerRay], game->rays, data);
	map_layer_door(&layers[LayerDoor], game->map.arr_doors, data);
	map_layer_map(&layers[LayerMap], &game->texture.map, data);
	map_layers_render(game->mlx, layers);
}
