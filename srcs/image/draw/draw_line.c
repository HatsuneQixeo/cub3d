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

void	image_draw_line(t_image image, const t_colour colour,
			const t_point start, const t_point end)
{
	const t_point	distance = (t_point){
		end.x - start.x,
		end.y - start.y
	};
	const int		total_step = ft_max(fabs(distance.x), fabs(distance.y));
	const t_point	step_length = (t_point){
		.x = distance.x / (double)total_step,
		.y = distance.y / (double)total_step
	};
	int				step;

	step = -1;
	while (++step < total_step)
	{
		image_draw_pixel(image, colour, (t_point){
			.x = start.x + (step_length.x * step),
			.y = start.y + (step_length.y * step)});
	}
}
