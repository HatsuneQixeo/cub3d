/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:47 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_point	point_add(const t_point point1, const t_point point2)
{
	t_point	new_point;

	new_point.x = point1.x + point2.x;
	new_point.y = point1.y + point2.y;
	return (new_point);
}

t_point	point_sub(const t_point point1, const t_point point2)
{
	t_point	new_point;

	new_point.x = point1.x - point2.x;
	new_point.y = point1.y - point2.y;
	return (new_point);
}

t_point	point_scale(const t_point point, const double scale)
{
	t_point	new_point;

	new_point.x = point.x * scale;
	new_point.y = point.y * scale;
	return (new_point);
}

t_point	point_unscale(const t_point point, const double scale)
{
	t_point	new_point;

	new_point.x = point.x / scale;
	new_point.y = point.y / scale;
	return (new_point);
}
