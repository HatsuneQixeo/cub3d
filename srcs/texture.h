#ifndef TEXTURE_H
# define TEXTURE_H

# include "image.h"

enum e_wall_texture_index
{
	North,
	East,
	South,
	West,
	wall_texture_count
};

typedef t_image	t_wall_textures[wall_texture_count];

typedef struct s_texture
{
	t_wall_textures	walls;
	t_image			minimap;
	t_image			player_icon;
	t_image			mouse_icon;
	t_colour		colour_floor;
	t_colour		colour_ceiling;
}			t_texture;


#endif
