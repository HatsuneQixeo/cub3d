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

t_point	point_add(const t_point a, const t_point b)
{
	const t_point	new_point = {
		.x = a.x + b.x,
		.y = a.y + b.y
	};

	return (new_point);
}

t_point	point_sub(const t_point a, const t_point b)
{
	const t_point	new_point = {
		.x = a.x - b.x,
		.y = a.y - b.y
	};

	return (new_point);
}

t_point	point_scale(const t_point point, const double scale)
{
	const t_point	new_point = {
		.x = point.x * scale,
		.y = point.y * scale
	};

	return (new_point);
}

t_point	point_unscale(const t_point point, const double scale)
{
	const t_point	new_point = {
		.x = point.x / scale,
		.y = point.y / scale
	};

	return (new_point);
}

t_point	point_round(const t_point point, double (*ft_round)(double))
{
	const t_point	new_point = {
		.x = ft_round(point.x),
		.y = ft_round(point.y)
	};

	return (new_point);
}
