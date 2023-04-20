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

# include <math.h>

typedef struct s_point
{
	double	x;
	double	y;
}			t_point;

/* Utilities */
double	point_magnitude(const t_point point);
double	point_distance(const t_point point1, const t_point point2);
double	point_dot(const t_point point1, const t_point point2);
double	point_cross(const t_point point1, const t_point point2);
t_point	point_rotate(const t_point point, const double angle);

/* Operators */
t_point	point_add(const t_point point1, const t_point point2);
t_point	point_sub(const t_point point1, const t_point point2);
t_point	point_scale(const t_point point, const double scale);
t_point	point_unscale(const t_point point, const double scale);
t_point	point_round(const t_point point, double (*ft_round)(double));

void	point_log(const char *prefix, const t_point point);

t_point	point_multiply(const t_point point1, const t_point point2);
t_point	point_normalize(const t_point point);
double	point_angle(const t_point point);
#endif
