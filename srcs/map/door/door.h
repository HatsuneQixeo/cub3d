#ifndef DOOR_H
# define DOOR_H

# include "image.h"

typedef struct s_door
{
	t_point			pos;
	int				is_open;
	unsigned int	animation_index;
	int				step;
}			t_door;

t_door	*door_new(t_point pos, int is_open, unsigned int animation_amount);

#endif
