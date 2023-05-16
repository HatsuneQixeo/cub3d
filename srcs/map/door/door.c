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
	if (is_open)
	{
		door->animation_index = 0;
		door->step = 1;
	}
	else
	{
		door->animation_index = animation_amount - 1;
		door->step = -1;
	}
	return (door);
}
