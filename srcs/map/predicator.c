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

	return (c == StartUp
		|| c == StartDown
		|| c == StartLeft
		|| c == StartRight);
}

/*
	Theorically this should be find instead of cmp,
	but due to the technical difficulty of determining the end of array,
	The door is instead created as 2darray, and terminating with NULL
*/
static int	cmp_doorpos(const void *p_door, const void *pos)
{
	const t_door	*door = p_door;

	return (ft_memcmp(&door->pos, pos, sizeof(t_point)));
}

int	cubmap_iswalkable(const t_map *map, const t_point pos)
{
	const char		c = map->layout[(int)pos.y][(int)pos.x];
	const t_door	**find;

	if (c == Wall)
		return (0);
	else if (!cubmap_isdoor(map, pos))
		return (1);
	find = (const t_door **)ft_aafind((void **)map->arr_doors, &pos, cmp_doorpos);
	ft_assert(find != NULL, "cubmap_iswalkable: could not find door at pos");
	return ((*find)->is_open);
}
