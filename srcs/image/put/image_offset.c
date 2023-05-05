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

double	putoffset_default(const double pos, const double size)
{
	return (pos);
	(void)size;
}

double	putoffset_centered(const double pos, const double size)
{
	return (pos - (size / 2));
}

double	putoffset_inverted(const double pos, const double size)
{
	return (pos - size);
}
