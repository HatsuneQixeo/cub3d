#include "cub3d.h"

static t_image	*texture_init_door(void *p_mlx, unsigned int *len)
{
	const char *const	filename = "sprites/weekender-girl-heart.xgif";
	char **const		strlist = ft_readfile(filename);
	t_image				*animation;
	unsigned int		i;

	cub3d_runtime_assertion(strlist != NULL, filename);
	*len = ft_strcount(strlist);
	animation = malloc(sizeof(*animation) **len);
	if (animation == NULL)
		return (NULL);
	i = -1;
	while (++i < *len)
	{
		animation[i] = image_readxpm(p_mlx, strlist[i],
				putoffset_default, putoffset_default);
		cub3d_runtime_assertion(image_good(&animation[i]), strlist[i]);
		image_setalpha(&animation[i], ft_min(0xff * ((double)i / *len), 0xbf));
	}
	ft_strlistclear(strlist);
	return (animation);
}

static void	texture_init_map(void *p_mlx, t_map_layers layers, const t_map *map)
{
	unsigned int	i;
	const t_point	size = point_sub(map_scale_point(map->size),
			(t_point){1, 1});

	i = -1;
	while (++i < layer_count)
	{
		layers[i] = image_create(p_mlx, size, (t_point){0, 0});
		cub3d_runtime_assertion(image_good(&layers[i]), "texture_init_map");
	}
	map_layer_layout(&layers[LayerMap], map);
}

void	texture_init(void *p_mlx, t_texture *texture, const t_map *map)
{
	{
		texture->mouse_icon = image_readxpm(p_mlx, "sprites/Normal-Select.xpm",
				putoffset_default, putoffset_default);
		cub3d_runtime_assertion(image_good(&texture->mouse_icon),
			"mouse_icon creation");
	}
	{
		texture_init_map(p_mlx, texture->map_layers, map);
	}
	{
		texture->walls[Invalid] = image_create(p_mlx, (t_point){1, 1},
				(t_point){0, 0});
		cub3d_runtime_assertion(image_good(&texture->walls[Invalid]),
			"invalid side of wall creation");
		texture->walls[Invalid].data[0] = 0x00000000;
	}
	{
		texture->door_animation = texture_init_door(p_mlx,
				&texture->door_animation_len);
		cub3d_runtime_assertion(texture->door_animation != NULL, "init_door");
	}
}
