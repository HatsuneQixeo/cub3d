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

# define IMAGE_CREATION_FAILED	"Image Creation Failed"

typedef double	(*t_offset)(const double pos, const double size);
/* Image Offset */
double	putoffset_default(const double pos, const double size);
double	putoffset_centered(const double pos, const double size);
double	putoffset_inverted(const double pos, const double size);

typedef struct s_mlx
{
	void	*p_mlx;
	void	*p_win;
}			t_mlx;

typedef struct s_image
{
	void		*p_image;
	t_colour	*data;
	t_offset	putoffset_x;
	t_offset	putoffset_y;
	t_point		size;
}				t_image;

int		image_getindex(const t_image *image, t_point pos);
/* Image Creation */
t_image	image_create(void *p_mlx, t_point size,
			t_offset putoffset_x, t_offset putoffset_y);
t_image	image_dup(void *p_mlx, const t_image *src);
t_image	image_readxpm(void *p_mlx, const char *path,
			t_offset putoffset_x, t_offset putoffset_y);
void	image_destroy(void *p_mlx, t_image *image);

/* Image Manipulation */
void	image_draw_pixel(t_image *image, t_colour colour, t_point at);
void	image_draw_line(t_image *image, t_colour colour,
			t_point start, t_point end);
void	image_fill(t_image *image, t_colour colour);
void	image_clean(t_image *image);

/* Rectangle */
void	image_draw_rectangle(t_image *image, t_colour colour,
			t_point start, t_point end);

/* Circle */
void	image_draw_circle(t_image *image, t_colour colour,
			t_point center, unsigned int radius);
void	draw_filled_circle(t_image *image, t_colour colour,
			t_point center, int radius);
void	image_fill_circle(t_image *image, t_colour colour);

/* Image Render */
void	image_put(t_mlx mlx, const t_image *image, t_point pos);
#endif
