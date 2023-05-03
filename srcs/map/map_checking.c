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

void	cubmap_showlsterror(const t_map map, const t_list *lst, const char *msg)
{
	const t_list	*it = lst;
	const t_point	*point;
	char			c;

	ft_putendl_fd("Error", 2);
	while (it != NULL)
	{
		point = lst->content;
		c = map.layout[(int)point->y][(int)point->x];
		if (ft_isprint(c))
			ft_dprintf(2, "	%s: %c", msg, c);
		else
			ft_dprintf(2, "	%s: \\%02x", msg, c);
		point_log(" at ", *point);
		it = it->next;
	}
}

int	cubmap_valid_player(const t_map map)
{
	t_list	*lst_player;
	int		status;

	lst_player = cubmap_gather_if(map, cubmap_isplayer);
	status = -1;
	if (lst_player == NULL)
		ft_putendl_fd("Error\nMissing Player", 2);
	else if (lst_player->next != NULL)
		cubmap_showlsterror(map, lst_player, "Duplicates Player");
	else
		status = 0;
	ft_lstclear(&lst_player, point_del);
	return (status);
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

int	cubmap_surrounded(const t_map map)
{
	t_list	*lst_missing;

	lst_missing = cubmap_gather_if(map, cubmap_isspace_atborder);
	if (lst_missing == NULL)
		return (0);
	cubmap_showlsterror(map, lst_missing, "Missing Wall at");
	ft_lstclear(&lst_missing, point_del);
	return (-1);
}