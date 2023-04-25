#include "cubmap.h"

/**
 * The identifier started off using t_ftis prototype,
 * but since these identifier are specifically designed for cubmap,
 * I figured it should be appropriate to make them smarter
 * to support more complex comfirmation
 */

int	cubmap_isplayer(const t_map *map, const t_point pos)
{
	const char	c = map->layout[(int)pos.y][(int)pos.x];

	return (c == StartUp
		|| c == StartDown
		|| c == StartLeft
		|| c == StartRight);
}

int	cubmap_isinvalid_unit(const t_map *map, const t_point pos)
{
	const char	c = map->layout[(int)pos.y][(int)pos.x];

	return (!(c == ' ' || c == Space || c == Wall
		|| cubmap_isplayer(map, pos)));
}

static int	isspace_orwall(int c)
{
	return (c == Space || c == Wall);
}

int	cubmap_isspace_atborder(const t_map *map, const t_point pos)
{
	const unsigned int	y = pos.y;
	const unsigned int	x = pos.x;

	if (map->layout[y][x] != Space)
		return (0);
	if (x == 0 || x == map->size.x - 1
		|| y == 0 || y == map->size.y - 1)
		return (1);
	return (!(isspace_orwall(map->layout[y - 1][x])
		&& isspace_orwall(map->layout[y][x - 1])
		&& isspace_orwall(map->layout[y + 1][x])
		&& isspace_orwall(map->layout[y][x + 1])));
}
