#include "cubmap.h"

static int	cubmap_isinvalid_door(const t_map *map, const t_point pos)
{
	const unsigned int	x = pos.x;
	const unsigned int	y = pos.y;
	char **const		layout = map->layout;
	const char			c = layout[y][x];

	if (!cubmap_isdoor(map, pos))
		return (0);
	if ((x == 0 || x == map->size.x - 1)
		|| (y == 0 || y == map->size.y - 1))
		return (1);
	return (!((layout[y - 1][x] == Wall && layout[y + 1][x] == Wall)
			|| (layout[y][x - 1] == Wall && layout[y][x + 1] == Wall)));
}

// const char	*err_msg = "Door cannot be placed without walls on either side"
// " or at the border: ";
int	cubmap_valid_door(const t_map map)
{
	t_list		*lst_invalid_door;
	const char	*err_msg = "Invalid Door";

	lst_invalid_door = cubmap_gather_if(map, cubmap_isinvalid_door);
	if (lst_invalid_door == NULL)
		return (0);
	cubmap_showlsterror(map, lst_invalid_door, err_msg);
	ft_lstclear(&lst_invalid_door, point_del);
	return (-1);
}
