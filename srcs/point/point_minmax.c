/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_minmax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "point.h"

/**
 * Didn't exactly work out the way I think,
 * instead of simplifying the expression,
 * these functions makes it pretty hard to read for more than half of the time,
 * because everything has to be done under the (t_point) format.
 */

t_point	point_minmax(const t_point min, const t_point point, const t_point max)
{
	const t_point	ret = {
		.x = ft_dminmax(min.x, point.x, max.x),
		.y = ft_dminmax(min.y, point.y, max.y)
	};

	return (ret);
}

t_point	point_min(const t_point a, const t_point b)
{
	const t_point	ret = {
		.x = ft_dmin(a.x, b.x),
		.y = ft_dmin(a.y, b.y)
	};

	return (ret);
}

t_point	point_max(const t_point a, const t_point b)
{
	const t_point	ret = {
		.x = ft_dmax(a.x, b.x),
		.y = ft_dmax(a.y, b.y)
	};

	return (ret);
}
