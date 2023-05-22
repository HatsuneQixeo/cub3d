/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef RAY_H
# define RAY_H

# include "point.h"

typedef struct s_map	t_map;

enum e_side
{
	SideUnknown = -1,
	SideHorizontal,
	SideVertical,
};

typedef struct s_ray
{
	t_point		direction;
	double		magnitude;
	t_point		hit;
	enum e_side	side;
}			t_ray;

t_ray	raycast(const t_map *map, t_point pos, t_point ray_direction,
			const char *target);

#endif
