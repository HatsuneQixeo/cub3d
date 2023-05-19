#include "door.h"

t_door	*door_new(const t_point pos, const int is_open,
			const unsigned int animation_amount)
{
	t_door	*door;

	door = malloc(sizeof(*door));
	if (door == NULL)
		return (NULL);
	door->pos = pos;
	door->is_open = is_open;
	door->animation_amount = animation_amount;
	door->animation_index = (is_open != 0) * (animation_amount - 1);
	door->step = 0;
	return (door);
}

/*
	Theorically this should be find instead of cmp,
	but due to the technical difficulty of determining the end of array,
	The door is instead created as 2darray, and terminate with NULL
*/
int	cmp_doorpos(const void *p_door, const void *p_pos)
{
	const t_door	*door = p_door;
	const t_point	*pos = p_pos;

	return (!(door->pos.x == pos->x && door->pos.y == pos->y));
	// return (ft_memcmp(&door->pos, pos, sizeof(t_point)));
}
