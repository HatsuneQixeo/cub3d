/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/10 22:58:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "libft.h"
# include "point.h"
# include "colour.h"
# include <mlx.h>
# include <math.h> /* ? */

enum e_wall_texture_index
{
	North,
	East,
	South,
	West,
	wall_texture_count
};

typedef struct s_size
{
	int	x;
	int	y;
}			t_size;

typedef struct s_image
{
	void		*p_image;
	t_colour	*data;
	t_size		size;
}				t_image;

typedef t_image	t_wall_texture[wall_texture_count];

typedef struct s_texture
{
	t_wall_texture	wall;
	t_colour		colour_floor;
	t_colour		colour_ceiling;
}			t_texture;

typedef struct s_mlx
{
	void	*p_mlx;
	void	*p_win;
}			t_mlx;

t_image	image_create(void *p_mlx, const t_size size);
t_image	image_readxpm(void *p_mlx, const char *path);
void	image_destroy(void *p_mlx, t_image *image);

void	image_draw_pixel(t_image *image, const t_colour colour, const t_size at);
void	image_draw_rectangle(t_image *image, const t_colour colour,
				const t_size start, const t_size end);
void	image_fill(t_image *image, const t_colour colour);
void	image_draw_line(t_image *image, const t_colour colour,
				const t_size start, const t_size end);

void	image_put(t_mlx mlx, t_image *p_image, t_size pos);

#endif
