#ifndef DOOR_H
# define DOOR_H

# include "image.h"

typedef struct s_door
{
	t_point			pos;
	int				is_open;
	unsigned int	animation_index;
	unsigned int	animation_amount;
	int				step;
}			t_door;

t_door	*door_new(t_point pos, int is_open, unsigned int animation_amount);

int		cmp_doorpos(const void *door, const void *pos);

#endif
