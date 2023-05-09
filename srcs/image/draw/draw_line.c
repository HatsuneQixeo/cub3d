/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	image_draw_line(t_image *image, const t_colour colour,
			const t_point start, const t_point end)
{
	const t_point	distance = point_sub(end, start);
	const int		total_step = ft_max(fabs(distance.x), fabs(distance.y));
	const t_point	step_length = point_downscale(distance, total_step);
	int				step;
	t_point			it;

	step = -1;
	it = start;
	while (++step < total_step)
	{
		image_setpixel(image, colour, it);
		it = point_add(it, step_length);
	}
}
