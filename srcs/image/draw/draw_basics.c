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

void	image_draw_pixel(t_image image, const t_colour colour, const t_point at)
{
	const t_point	rounded = point_round(at, trunc);

	if (rounded.x < 0 || rounded.x >= image.size.x)
	{
		printf("x: %f, size: %f\n", at.x, image.size.x);
		return ;
	}
	if (rounded.y < 0 || rounded.y >= image.size.y)
	{
		printf("y: %f, size: %f\n", at.y, image.size.y);
		return ;
	}
	ft_assert(0 <= rounded.x && rounded.x < image.size.x,
		"image_draw_pixel: out of range: x");
	ft_assert(0 <= rounded.y && rounded.y < image.size.y,
		"image_draw_pixel: out of range: y");
	ft_assert(image.data != NULL,
		"image_draw_pixel: NULL image.data");
	image.data[(unsigned int)((rounded.y * image.size.x) + rounded.x)] = colour;
}

void	image_draw_rectangle(t_image image, const t_colour colour,
				const t_point start, const t_point end)
{
	t_point	index;

	index.y = start.y - 1;
	while (++index.y < end.y)
	{
		index.x = start.x - 1;
		while (++index.x < end.x)
			image_draw_pixel(image, colour, index);
	}
}

void	image_fill(t_image image, const t_colour colour)
{
	// image_draw_rectangle(image, colour, (t_point){0, 0}, image.size);
	ft_intset((int *)image.data, image.size.x * image.size.y, colour);
}

void	image_clear(t_image image)
{
	image_fill(image, colour_from_rgba(0, 0, 0, 255));
}
