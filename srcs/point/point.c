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
	printf("%s[x: %f, y: %f]\n", prefix, point.x, point.y);
}

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

int	point_inbound(const t_point point, const t_point size)
{
	return ((0 <= point.x && point.x < size.x)
		&& (0 <= point.y && point.y < size.y));
}
