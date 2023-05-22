/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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

typedef struct s_texture
{
	t_wall_textures	walls;
	t_image			map;
	t_image			mouse_icon;
	t_colour		colour_floor;
	t_colour		colour_ceiling;
	t_image			*door_animation;
	unsigned int	door_animation_len;
}			t_texture;

#endif
