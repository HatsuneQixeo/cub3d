/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	image_put(const t_mlx mlx, const t_image *image, const t_point pos)
{
	t_point	put;

	ft_assert(image != NULL, "image_put: NULL image");
	ft_assert(image->p_image != NULL, "image_put: NULL image.p_image");
	ft_assert(image->putoffset_x != NULL, "image_put: NULL putoffset_x");
	ft_assert(image->putoffset_y != NULL, "image_put: NULL putoffset_y");
	put = (t_point){
		.x = image->putoffset_x(pos.x, image->size.x),
		.y = image->putoffset_y(pos.y, image->size.y)
	};
	mlx_put_image_to_window(mlx.p_mlx, mlx.p_win, image->p_image, put.x, put.y);
}
