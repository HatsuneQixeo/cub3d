/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:47 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

double	point_magnitude(const t_point point)
{
	return (sqrt(pow(point.x, 2) + pow(point.y, 2)));
}

double	point_distance(const t_point point1, const t_point point2)
{
	return (sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2)));
}

double	point_dot(const t_point point1, const t_point point2)
{
	return (point1.x * point2.x + point1.y * point2.y);
}

double	point_cross(const t_point point1, const t_point point2)
{
	return (point1.x * point2.y - point1.y * point2.x);
}

t_point	point_rotate(const t_point point, const double angle)
{
	t_point	new_point;

	new_point.x = point.x * cos(angle) - point.y * sin(angle);
	new_point.y = point.x * sin(angle) + point.y * cos(angle);
	return (new_point);
}
