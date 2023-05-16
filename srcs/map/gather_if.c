#include "cubmap.h"

t_list	*cubmap_gather_if(const t_map map, t_cubmapis ft_is)
{
	t_list	*lst_player;
	t_point	it;

	lst_player = NULL;
	it.y = map.size.y;
	while (it.y--)
	{
		it.x = map.size.x;
		while (it.x--)
		{
			if (ft_is(&map, it))
				ft_lstadd_front(&lst_player, ft_lstnew(point_new(it.x, it.y)));
		}
	}
	return (lst_player);
}
