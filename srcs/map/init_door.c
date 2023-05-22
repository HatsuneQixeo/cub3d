/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cubmap.h"

static void	door_init(t_map *map, const t_list *lst_door,
			const unsigned int animation_amount)
{
	const unsigned int	len = ft_lstsize(lst_door);
	unsigned int		i;
	const t_point		*pos;
	char				c;

	map->arr_doors = malloc(sizeof(t_door *) * (len + 1));
	if (map->arr_doors == NULL)
		return ;
	i = 0;
	while (lst_door != NULL)
	{
		pos = lst_door->content;
		c = map->layout[(int)pos->y][(int)pos->x];
		lst_door = lst_door->next;
		map->arr_doors[i++] = door_new(*pos, c == DoorOpen, animation_amount);
	}
	map->arr_doors[i] = NULL;
}

void	cubmap_door_init(t_map *map, const unsigned int animation_amount)
{
	t_list	*lst_door;

	lst_door = cubmap_gather_if(*map, cubmap_isdoor);
	door_init(map, lst_door, animation_amount);
	ft_lstclear(&lst_door, point_del);
}
