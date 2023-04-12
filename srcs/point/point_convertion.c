/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_convertion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:47 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_pixelpoint	to_pixelpoint(const t_point point)
{
	// return ((t_pixelpoint){.x = round(point.x), .y = round(point.y)});
	return ((t_pixelpoint){.x = point.x, .y = point.y});
}

t_point	to_point(const t_pixelpoint pixelpoint)
{
	return ((t_point){.x = pixelpoint.x, .y = pixelpoint.y});
}
