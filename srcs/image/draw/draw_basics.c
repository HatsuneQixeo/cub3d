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

#ifndef DRAW_WARNING
# define DRAW_WARNING	1
#endif

int	image_getindex(const t_image *image, const t_point pos)
{
	const int	index = (pos.y * image->size.x) + pos.x;

	if (DRAW_WARNING && index >= image->size.y * image->size.x)
	{
		point_log("image_getindex: outofbound", pos);
		point_log("image_getindex: size", image->size);
	}
	return (index);
}

/* Took out the round safety for performance */
void	image_setpixel(t_image *image, const t_colour colour, const t_point pos)
{
	if (!(0 <= pos.x && pos.x < image->size.x))
	{
		if (DRAW_WARNING)
			printf("outofrange x: %f, size: %f\n", pos.x, image->size.x);
		return ;
	}
	if (!(0 <= pos.y && pos.y < image->size.y))
	{
		if (DRAW_WARNING)
			printf("outofrange y: %f, size: %f\n", pos.y, image->size.y);
		return ;
	}
	image->data[image_getindex(image, pos)] = colour;
}

t_colour	image_getpixel(const t_image *image, const t_point pos)
{
	const unsigned int	index = image_getindex(image, pos);

	return (image->data[index]);
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
			image_setpixel(image, colour, it);
	}
}

void	image_fill(t_image *image, const t_colour colour)
{
	ft_intset((int *)image->data, image->size.x * image->size.y, colour);
}

void	image_clean(t_image *image)
{
	image_fill(image, colour_from_rgba(0, 0, 0, 255));
}
