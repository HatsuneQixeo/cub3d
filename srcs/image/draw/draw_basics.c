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

void	image_draw_pixel(t_image image, const t_colour colour, const t_pixelpoint at)
{
	if (at.x < 0 || at.x >= image.size.x)
	{
		printf("x: %d, size: %d\n", at.x, image.size.x);
		return ;
	}
	if (at.y < 0 || at.y >= image.size.y)
	{
		printf("y: %d, size: %d\n", at.y, image.size.y);
		return ;
	}
	ft_assert(0 <= at.x && at.x < image.size.x,
		"image_draw_pixel: out of range: x");
	ft_assert(0 <= at.y && at.y < image.size.y,
		"image_draw_pixel: out of range: y");
	ft_assert(image.data != NULL,
		"image_draw_pixel: NULL image.data");
	image.data[(at.y * image.size.x) + at.x] = colour;
}

void	image_draw_rectangle(t_image image, const t_colour colour,
				const t_pixelpoint start, const t_pixelpoint end)
{
	t_pixelpoint	index;

	index.y = start.y;
	while (index.y < end.y)
	{
		index.x = start.x;
		while (index.x < end.x)
		{
			image_draw_pixel(image, colour, index);
			index.x++;
		}
		index.y++;
	}
}

void	image_fill(t_image image, const t_colour colour)
{
	image_draw_rectangle(image, colour, (t_pixelpoint){0, 0}, image.size);
}

void	image_clear(t_image image)
{
	image_fill(image, colour_from_percentage(0, 0, 0, 1));
}

// void	image_draw_triangle(t_image image, const t_colour colour, const t_pixelpoint points[3])
// {
// 	image_draw_line(image, colour, points[0], points[1]);
// 	image_draw_line(image, colour, points[1], points[2]);
// 	image_draw_line(image, colour, points[2], points[0]);
// 	/* For loop and bsp let's goo */
// }
