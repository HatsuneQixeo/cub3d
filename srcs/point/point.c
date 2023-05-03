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
#include <stdlib.h>

t_point	*point_new(const double x, const double y)
{
	t_point	*point;

	point = malloc(sizeof(t_point));
	if (point == NULL)
		return (NULL);
	point->x = x;
	point->y = y;
	return (point);
}

void	point_del(void *content)
{
	free(content);
}

void	point_log(const char *prefix, const t_point point)
{
	// printf("[%-20s] x: %6.2f, y: %6.2f\n", prefix, point.x, point.y);
	printf("[%-20s] x: %f, y: %f\n", prefix, point.x, point.y);
}

/* Bunch of math I have no idea */
/* Likely math that won't come in handy in this project */

// t_point	point_normalize(const t_point src)
// {
// 	return (point_downscale(src, point_magnitude(src)));
// }

// t_point	point_lerp(const t_point point1, const t_point point2, const double t)
// {
// 	return (point_add(point1, point_upscale(point_sub(point2, point1), t)));
// }

// t_point	point_reflect(const t_point point, const t_point normal)
// {
// 	return (point_sub(point, point_upscale(normal, 2 * point_dot(point, normal))));
// }

// t_point	point_midpoint(const t_point point1, const t_point point2)
// {
// 	return (point_upscale(point_add(point1, point2), .50));
// }

// t_point	point_project(const t_point point, const t_point normal)
// {
// 	return (point_upscale(normal,
// 			point_dot(point, normal) / point_dot(normal, normal)));
// }

// t_point	point_reject(const t_point point, const t_point normal)
// {
// 	return (point_sub(point, point_project(point, normal)));
// }

// t_point	point_from_angle(const double angle)
// {
// 	const t_point	point = {
// 		.x = cos(angle),
// 		.y = sin(angle)
// 	};

// 	return (point);
// }

// t_point	point_from_polar(const double magnitude, const double angle)
// {
// 	return (point_upscale(point_from_angle(angle), magnitude));
// }

double	point_angle(const t_point point)
{
	/* Remember to change this back? Or maybe just leave it as it is? */
	return (atan2(point.y, point.x) + M_PI_2);
}

t_point	point_sign(const t_point direction)
{
	const t_point	point = {
		.x = -(direction.x < 0) + (direction.x > 0),
		.y = -(direction.y < 0) + (direction.y > 0)
	};

	return (point);
}
