#ifndef TEXTURE_H
# define TEXTURE_H

# include "image.h"

enum e_wall_texture_index
{
	North,
	East,
	South,
	West,
	Invalid,
	wall_texture_count,
};

typedef t_image	t_wall_textures[wall_texture_count];

enum e_layer_index
{
	LayerPlayer,
	LayerRay,
	LayerInteract,
	LayerDoor,
	LayerMap,
	layer_count
};
// enum e_layer_index
// {
// 	LayerPlayer,
// 	LayerDoor,
// 	LayerMap,
// 	layer_count
// };
typedef t_image	t_map_layers[layer_count];

typedef struct s_texture
{
	t_wall_textures	walls;
	t_map_layers	map_layers;
	t_image			mouse_icon;
	t_colour		colour_floor;
	t_colour		colour_ceiling;
	t_image			*door_animation;
	unsigned int	door_animation_len;
}			t_texture;

#endif
