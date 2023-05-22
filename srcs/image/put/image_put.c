/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_put.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "image.h"

void	image_put(t_mlx mlx, const t_image *image, const t_point pos)
{
	const t_point	put = point_add(pos, image->putoffset);

	ft_assert(image != NULL, "image_put: NULL image");
	ft_assert(image->p_image != NULL, "image_put: NULL image.p_image");
	mlx_put_image_to_window(mlx.p_mlx, mlx.p_win, image->p_image, put.x, put.y);
}
