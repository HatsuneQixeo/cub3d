/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"
#include <stdio.h>

void	point_log(const char *prefix, const t_point point)
{
	printf("%sx: %f, y: %f\n", prefix, point.x, point.y);
}

/* Bunch of math I have no idea */

t_point	point_normalize(const t_point point)
{
	t_point			new_point;
	const double	magnitude = point_magnitude(point);

	new_point.x = point.x / magnitude;
	new_point.y = point.y / magnitude;
	return (new_point);
}

t_point	point_multiply(const t_point point1, const t_point point2)
{
	const t_point	new_point = {
		.x = point1.x * point2.x,
		.y = point1.y * point2.y
	};

	return (new_point);
}

// t_point	point_lerp(const t_point point1, const t_point point2, const double t)
// {
// 	t_point	new_point;

// 	new_point.x = point1.x + (point2.x - point1.x) * t;
// 	new_point.y = point1.y + (point2.y - point1.y) * t;
// 	return (new_point);
// }

// t_point	point_reflect(const t_point point, const t_point normal)
// {
// 	t_point	new_point;

// 	new_point = point_sub(point, point_scale(normal, 2 * point_dot(point, normal)));
// 	return (new_point);
// }

// t_point	point_midpoint(const t_point point1, const t_point point2)
// {
// 	t_point	new_point;

// 	new_point.x = (point1.x + point2.x) / 2;
// 	new_point.y = (point1.y + point2.y) / 2;
// 	return (new_point);
// }

// t_point	point_project(const t_point point, const t_point normal)
// {
// 	t_point	new_point;

// 	new_point = point_scale(normal, point_dot(point, normal) / point_dot(normal, normal));
// 	return (new_point);
// }

// t_point	point_reject(const t_point point, const t_point normal)
// {
// 	t_point	new_point;

// 	new_point = point_sub(point, point_project(point, normal));
// 	return (new_point);
// }

// t_point	point_from_angle(const double angle)
// {
// 	t_point	point;

// 	point.x = cos(angle);
// 	point.y = sin(angle);
// 	return (point);
// }

// t_point	point_from_polar(const double magnitude, const double angle)
// {
// 	t_point	point;

// 	point.x = magnitude * cos(angle);
// 	point.y = magnitude * sin(angle);
// 	return (point);
// }

double	point_angle(const t_point point)
{
	return (atan2(point.y, point.x));
}
