#include "cubmap.h"

static int	isspace_orwall(const t_map *map, const t_point pos)
{
	const char	c = map->layout[(int)pos.y][(int)pos.x];

	return (c == Space || c == Wall || cubmap_isplayer(map, pos));
}

static int	cubmap_ismissingborder(const t_map *map, const t_point pos)
{
	const unsigned int	y = pos.y;
	const unsigned int	x = pos.x;

	if (!(map->layout[y][x] == Space || cubmap_isplayer(map, pos)))
		return (0);
	if ((x == 0 || x == map->size.x - 1)
		|| (y == 0 || y == map->size.y - 1))
		return (1);
	return (!(isspace_orwall(map, pos)
			&& isspace_orwall(map, pos)
			&& isspace_orwall(map, pos)
			&& isspace_orwall(map, pos)));
}

int	cubmap_surrounded(const t_map map)
{
	t_list	*lst_missing;

	lst_missing = cubmap_gather_if(map, cubmap_ismissingborder);
	if (lst_missing == NULL)
		return (0);
	cubmap_showlsterror(map, lst_missing, "Missing Wall at");
	ft_lstclear(&lst_missing, point_del);
	return (-1);
}
