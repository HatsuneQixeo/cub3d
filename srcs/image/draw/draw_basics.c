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
	const unsigned int	index = (pos.y * image->size.x) + pos.x;

	if (DRAW_WARNING && index >= image->size.y * image->size.x)
	{
		point_log("image_getindex: outofbound", pos);
		point_log("image_getindex: size", image->size);
	}
	return (index);
}

void	image_setpixel(t_image *image, const t_colour colour, const t_point pos)
{
	if ((0 <= pos.x && pos.x < image->size.x)
			&& (0 <= pos.y && pos.y < image->size.y))
		image->data[image_getindex(image, pos)] = colour;
	else if (DRAW_WARNING)
	{
		point_log("image_setpixel: outofbound", pos);
		point_log("image_setpixel: size", image->size);
	}
}

t_colour	image_getpixel(const t_image *image, const t_point pos)
{
	return (image->data[image_getindex(image, pos)]);
}
