#ifndef CUBMAP_H
# define CUBMAP_H

# include "point.h"
# include "libft.h"
# include "door.h"
# include "texture.h"

typedef struct s_map
{
	t_point	size;
	char	**layout;
	t_door	**arr_doors;
}			t_map;

enum e_mapunit
{
	Void = ' ',
	Space = '0',
	Wall = '1',
	DoorClose = '2',
	DoorOpen = '3',
	StartUp = 'N',
	StartDown = 'S',
	StartLeft = 'W',
	StartRight = 'E',
};

typedef struct s_player	t_player;

/* Predicator */
typedef int	(*t_cubmapis)(const t_map *map, t_point pos);
int			cubmap_isdoor(const t_map *map, t_point pos);
int			cubmap_isplayer(const t_map *map, t_point pos);
int			cubmap_iswalkable(const t_map *map, t_point pos);

t_list		*cubmap_gather_if(t_map map, t_cubmapis ft_is);
void		cubmap_showlsterror(t_map map, const t_list *lst, const char *msg);
/* Validator */
int			cubmap_valid_unit(t_map map);
int			cubmap_surrounded(t_map map);
int			cubmap_valid_door(t_map map);

/* Initialise */
int			cubmap_getmap(void *p_mlx, const char *path,
				t_map *map, t_texture *texture);
int			cubmap_player_init(t_map map, t_player *player);
void		cubmap_door_init(t_map *map, unsigned int animation_amount);

#endif
