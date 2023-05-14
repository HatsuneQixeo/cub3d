/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_offset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

double	putoffset_default(const double size)
{
	return (0);
	(void)size;
}

double	putoffset_centered(const double size)
{
	return (-(size / 2));
}

double	putoffset_inverted(const double size)
{
	return (-size);
}

t_point	image_getoffset(const t_image *image)
{
	const t_point	offset = {
		.x = image->putoffset_x(image->size.x),
		.y = image->putoffset_y(image->size.y)
	};

	return (offset);
}
