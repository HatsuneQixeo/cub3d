#ifndef PLAYER_H
# define PLAYER_H

# include "libft.h"
# include "point.h"
# include "ray.h"
# include "hook_mouse.h"
# include "hook_key.h"

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
	t_point	target;
}			t_player;

t_point	player_getvector(const t_keys keys);
void	player_move(t_player *player, t_point direction, const t_map *map);
void	player_target(t_player *player, const t_map *map);

#endif
