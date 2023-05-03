#ifndef RAY_H
# define RAY_H

# include "point.h"

enum e_side
{
	Vertical,
	Horizontal
};

typedef struct s_ray
{
	t_point		direction;
	double		distance_traveled;
	t_point		hit;
	enum e_side	side;
}			t_ray;

t_ray	raycast(char **map, const t_point pos, const t_point ray_direction);

#endif
