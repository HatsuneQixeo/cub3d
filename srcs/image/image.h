/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "libft.h" /* ? */
# include "point.h"
# include "colour.h"
# include <mlx.h>

enum e_wall_texture_index
{
	North,
	East,
	South,
	West,
	wall_texture_count
};

typedef int		(*t_offset)(const int pos, const int size);
/* Image Offset */
int		putoffset_default(const int pos, const int size);
int		putoffset_centered(const int pos, const int size);
int		putoffset_inverted(const int pos, const int size);

typedef struct s_image
{
	void			*p_image;
	t_colour		*data;
	t_offset		putoffset_x;
	t_offset		putoffset_y;
	t_pixelpoint	size;
}				t_image;

typedef t_image	t_wall_textures[wall_texture_count];

typedef struct s_texture
{
	t_wall_textures	walls;
	t_image			player_icon;
	t_image			mouse_icon;
	t_colour		colour_floor;
	t_colour		colour_ceiling;
}			t_texture;

typedef struct s_mlx
{
	void	*p_mlx;
	void	*p_win;
}			t_mlx;

/* Image Creation */
t_image	image_create(void *p_mlx, const t_pixelpoint size,
			t_offset putoffset_x, t_offset putoffset_y);
t_image	image_readxpm(void *p_mlx, const char *path);
void	image_destroy(void *p_mlx, t_image *image);

/* Image Manipulation */
void	image_draw_pixel(t_image image, const t_colour colour, const t_pixelpoint at);
void	image_draw_line(t_image image, const t_colour colour,
			const t_pixelpoint start, const t_pixelpoint end);
void	image_fill(t_image image, const t_colour colour);
void	image_clear(t_image image);

/* Rectangle */
void	image_draw_rectangle(t_image image, const t_colour colour,
			const t_pixelpoint start, const t_pixelpoint end);

/* Circle */
void	image_draw_circle(t_image image, const t_colour colour,
			const t_pixelpoint center, const unsigned int radius);
void	draw_filled_circle(t_image image, const t_colour colour,
			const t_pixelpoint center, const int radius);
void	image_fill_circle(t_image image, t_colour colour);

/* Image Render */
void	image_put(const t_mlx mlx, const t_image image, const t_pixelpoint pos);
#endif
