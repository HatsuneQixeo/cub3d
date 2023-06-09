/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:05 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "image.h"

#ifndef DRAW_WARNING
# define DRAW_WARNING	1
#endif

#ifndef IMAGE_OUT_OF_BOUND_CHECK
# define IMAGE_OUT_OF_BOUND_CHECK	0
#endif

/*
	Certain amount of readability is sacrificed for the sake of performace,
	since these functions are called very very frequently for image manipulation

	Would not have to if norminette allows function macro, duh.
	It would have make these functions literally have no performance penalty
	 without giving up any readability.

	Don't think inlining is optimizing anything either,
	not even getindex called in this file is getting optimised.

	These functions are still pretty expensive to put in a loop,
	regardless of the optimisation.
	Shame, real shame,
	one of the case where norminette is literally
	 holding me back from writing clean code.
*/

int	image_getindex(const t_image *const image, const t_point pos)
{
	const int	index = (pos.y * image->size.x) + pos.x;

	if (IMAGE_OUT_OF_BOUND_CHECK && DRAW_WARNING
		&& index >= image->size.y * image->size.x)
	{
		point_log("image_getindex: outofbound", pos);
		point_log("image_getindex: size", image->size);
	}
	return (index);
}

void	image_setpixel(const t_image *const image, const t_colour colour,
			const t_point pos)
{
	if (!IMAGE_OUT_OF_BOUND_CHECK
		|| ((0 <= pos.x && pos.x < image->size.x)
			&& (0 <= pos.y && pos.y < image->size.y)))
		image->data[(int)((pos.y * image->size.x) + pos.x)] = colour;
	else if (DRAW_WARNING)
	{
		point_log("image_setpixel: outofbound", pos);
		point_log("image_setpixel: size", image->size);
	}
}

t_colour	image_getpixel(const t_image *const image, const t_point pos)
{
	return (image->data[(int)((pos.y * image->size.x) + pos.x)]);
}
