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
			const t_point begin, const t_point end)
{
	const t_point	vector = point_sub(end, begin);
	const int		total_step = ft_max(fabs(vector.x), fabs(vector.y));
	const t_point	step_length = point_downscale(vector, total_step);
	int				step;
	t_point			it;

	step = -1;
	if (isnan(step_length.x) || isnan(step_length.y))
		return (point_log("image_draw_line: step_length is NaN", step_length));
	it = begin;
	while (++step < total_step)
	{
		image_setpixel(image, colour, point_apply(it, trunc));
		it = point_add(it, step_length);
	}
}
