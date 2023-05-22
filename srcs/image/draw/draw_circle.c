/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:05 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "image.h"

static void	doro(t_image *image, const t_colour colour, const t_point center,
			const t_point point)
{
	image_setpixel(image, colour,
		(t_point){center.x + point.x, center.y + point.y});
	image_setpixel(image, colour,
		(t_point){center.x + point.y, center.y + point.x});
	image_setpixel(image, colour,
		(t_point){center.x - point.x, center.y + point.y});
	image_setpixel(image, colour,
		(t_point){center.x - point.y, center.y + point.x});
	image_setpixel(image, colour,
		(t_point){center.x + point.x, center.y - point.y});
	image_setpixel(image, colour,
		(t_point){center.x + point.y, center.y - point.x});
	image_setpixel(image, colour,
		(t_point){center.x - point.x, center.y - point.y});
	image_setpixel(image, colour,
		(t_point){center.x - point.y, center.y - point.x});
}

/* Outline */
void	image_draw_circle(t_image *image, const t_colour colour,
				const t_point center, const unsigned int radius)
{
	t_point	point;
	int		error;

	point = (t_point){.x = 0, .y = radius};
	error = 1 - radius;
	while (point.x <= point.y)
	{
		doro(image, colour, center, point);
		if (error <= 0)
		{
			error += 2 * point.x + 1;
			point.x++;
		}
		else
		{
			error += 2 * (point.x - point.y) + 1;
			point.x++;
			point.y--;
		}
	}
	if (radius > 1)
		image_draw_circle(image, colour, center, radius - 1);
}

void	draw_filled_circle(t_image *image, const t_colour colour,
			const t_point center, const unsigned int radius)
{
	t_point	index;

	index.y = center.y - radius - 1;
	while (++index.y < center.y + radius)
	{
		index.x = center.x - radius - 1;
		while (++index.x < center.x + radius)
		{
			if (point_distance(index, center) <= radius)
				image_setpixel(image, colour, index);
		}
	}
}

void	image_fill_circle(t_image *image, const t_colour colour)
{
	const t_point	center = point_apply(point_upscale(image->size, .5), trunc);
	const int		min = ft_min(image->size.x, image->size.y);
	const double	radius = (double)(min - !(min & 0b1)) / 2;

	image_clean(image);
	image_draw_circle(image, colour, center, radius);
}
