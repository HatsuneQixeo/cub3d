/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:05 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "image.h"

void	image_draw_line(t_image *image, const t_colour colour,
			const t_point begin, const t_point end)
{
	const t_point		vector = point_sub(end, begin);
	const unsigned int	total_step = ft_dmax(fabs(vector.x), fabs(vector.y));
	const t_point		step_length = point_downscale(vector, total_step);
	unsigned int		step;
	t_point				it;

	step = -1;
	it = begin;
	while (++step < total_step)
	{
		image_setpixel(image, colour, point_apply(it, trunc));
		it = point_add(it, step_length);
	}
}
