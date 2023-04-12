/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_convertion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:47 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_point	point_round(const t_point point, double (*ft_round)(double))
{
	return ((t_point){.x = ft_round(point.x), .y = ft_round(point.y)});
}
