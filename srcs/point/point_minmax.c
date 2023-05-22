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

t_point	point_min(const t_point point, const t_point min)
{
	const t_point	ret = {
		.x = ft_dmin(min.x, point.x),
		.y = ft_dmin(min.y, point.y)
	};

	return (ret);
}

t_point	point_max(const t_point point, const t_point max)
{
	const t_point	ret = {
		.x = ft_dmax(max.x, point.x),
		.y = ft_dmax(max.y, point.y)
	};

	return (ret);
}
