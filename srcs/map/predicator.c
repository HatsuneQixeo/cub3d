/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predicator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cubmap.h"

/**
 * The identifier started off using t_ftis prototype,
 * but since these identifier are specifically designed for cubmap,
 * I figured it should be appropriate to make them smarter
 * to support more complex comfirmation
 */

int	cubmap_isdoor(const t_map *map, const t_point pos)
{
	const char	c = map->layout[(int)pos.y][(int)pos.x];

	return (c == DoorOpen || c == DoorClose);
}

int	cubmap_isplayer(const t_map *map, const t_point pos)
{
	const char	c = map->layout[(int)pos.y][(int)pos.x];

	return (c == StartUp || c == StartDown
		|| c == StartLeft || c == StartRight);
}

int	cubmap_iswalkable(const t_map *map, const t_point pos)
{
	const char		c = map->layout[(int)pos.y][(int)pos.x];
	const t_door	**find;
	const t_point	rounded_pos = point_apply(pos, trunc);

	if (c == Wall)
		return (0);
	else if (!cubmap_isdoor(map, pos))
		return (1);
	find = (const t_door **)ft_aafind((void **)map->arr_doors,
			&rounded_pos, cmp_doorpos);
	ft_assert(find != NULL, "cubmap_iswalkable: could not find door at pos");
	return ((*find)->is_open);
}

// int	cubmap_iswalkable(const t_map *map, const t_point pos)
// {
// 	const char	c = map->layout[(int)pos.y][(int)pos.x];

// 	return (!(c == Wall || c == DoorClose));
// }
