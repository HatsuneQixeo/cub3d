#ifndef CUBMAP_H
# define CUBMAP_H

# include "point.h"
# include "libft.h"


typedef struct s_map
{
	t_point	size;
	char	**layout;
}			t_map;

enum e_mapunit
{
	Space = '0',
	Wall = '1',
	StartUp = 'N',
	StartDown = 'S',
	StartLeft = 'W',
	StartRight = 'E',
};

typedef int	(*t_cubmapis)(const t_map *map, const t_point point);

int	cubmap_isplayer(const t_map *map, const t_point pos);
int	cubmap_isinvalid_unit(const t_map *map, const t_point pos);
int	cubmap_isspace_atborder(const t_map *map, const t_point pos);

#endif
