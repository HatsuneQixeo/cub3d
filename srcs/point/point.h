/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "libmath.h"

# define POINT_DEBUG(point)	point_log(#point, point)

typedef struct s_point
{
	double	x;
	double	y;
}			t_point;

/* Utilities */
double	point_magnitude(t_point point);
double	point_distance(t_point point1, t_point point2);
double	point_dot(t_point point1, t_point point2);
double	point_cross(t_point point1, t_point point2);
t_point	point_rotate(t_point point, double angle);

/* Minmax */
t_point	point_min(t_point point, t_point min);
t_point	point_max(t_point point, t_point max);
t_point	point_minmax(t_point min, t_point point, t_point max);

/* Operators */
t_point	point_add(t_point point1, t_point point2);
t_point	point_sub(t_point point1, t_point point2);
t_point	point_upscale(t_point point, double scale);
t_point	point_downscale(t_point point, double scale);
t_point	point_apply(t_point point, double (*func)(double));

t_point	*point_new(double x, double y);
void	point_del(void *content);
void	point_log(const char *prefix, t_point point);
int		point_inbound(t_point point, t_point size);

t_point	point_multiply(t_point point1, t_point point2);
t_point	point_normalize(t_point point);
double	point_angle(t_point point);
t_point	point_sign(t_point direction);
#endif
