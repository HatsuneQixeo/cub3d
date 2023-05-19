#ifndef RAY_H
# define RAY_H

# include "point.h"
# include "cubmap.h"

enum e_side
{
	SideUnknown = -1,
	SideHorizontal,
	SideVertical,
};

typedef struct s_ray
{
	t_point		direction;
	double		distance_traveled;
	t_point		hit;
	enum e_side	side;
}			t_ray;

t_ray	raycast(const t_map *map, t_point pos, t_point ray_direction,
			const char *hit);

#endif
