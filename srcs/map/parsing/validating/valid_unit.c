/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_unit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cubmap.h"

static int	cubmap_isinvalid_unit(const t_map *map, const t_point pos)
{
	const char	c = map->layout[(int)pos.y][(int)pos.x];

	return (!(c == Void || c == Space || c == Wall
			|| cubmap_isdoor(map, pos)
			|| cubmap_isplayer(map, pos)));
}

int	cubmap_valid_unit(const t_map map)
{
	t_list	*lst_invalid_unit;

	lst_invalid_unit = cubmap_gather_if(map, cubmap_isinvalid_unit);
	if (lst_invalid_unit == NULL)
		return (0);
	cubmap_showlsterror(map, lst_invalid_unit, "Invalid Unit");
	ft_lstclear(&lst_invalid_unit, point_del);
	return (-1);
}
