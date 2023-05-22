/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "image.h"

void	image_fill(t_image *image, const t_colour colour)
{
	ft_intset((int *)image->data, image->size.x * image->size.y, colour);
}

void	image_clean(t_image *image)
{
	image_fill(image, 0xff000000);
}

void	image_setalpha(t_image *image, const t_colour_byte value)
{
	unsigned int		i;
	const unsigned int	len = image->size.y * image->size.x;

	i = -1;
	while (++i < len)
		colour_setmask(&image->data[i], value, ValueA);
}
