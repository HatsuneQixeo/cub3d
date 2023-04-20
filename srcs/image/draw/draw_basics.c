/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

int	image_getindex(const t_image *image, const t_point pos)
{
	return ((pos.y * image->size.x) + pos.x);
}

void	image_draw_pixel(t_image *image, const t_colour colour, const t_point at)
{
	const t_point	rounded = point_round(at, trunc);

	if (!(0 <= rounded.x && rounded.x < image->size.x))
	{
		printf("outofrange x: %f, size: %f\n", at.x, image->size.x);
		return ;
	}
	if (!(0 <= rounded.y && rounded.y < image->size.y))
	{
		printf("ourofrange y: %f, size: %f\n", at.y, image->size.y);
		return ;
	}
	ft_assert(0 <= rounded.x && rounded.x < image->size.x,
		"image_draw_pixel: out of range: x");
	ft_assert(0 <= rounded.y && rounded.y < image->size.y,
		"image_draw_pixel: out of range: y");
	ft_assert(image->data != NULL, "image_draw_pixel: NULL image->data");
	image->data[image_getindex(image, rounded)] = colour;
}

void	image_draw_rectangle(t_image *image, const t_colour colour,
				const t_point start, const t_point end)
{
	t_point	it;

	it.y = start.y - 1;
	while (++it.y < end.y)
	{
		it.x = start.x - 1;
		while (++it.x < end.x)
			image_draw_pixel(image, colour, it);
	}
}

void	image_fill(t_image *image, const t_colour colour)
{
	// image_draw_rectangle(image, colour, (t_point){0, 0}, image->size);
	ft_intset((int *)image->data, image->size.x * image->size.y, colour);
}

void	image_clear(t_image *image)
{
	image_fill(image, colour_from_rgba(0, 0, 0, 255));
}
