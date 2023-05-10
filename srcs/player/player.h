#ifndef PLAYER_H
# define PLAYER_H

# include "point.h"
# include "hook_mouse.h"
# include "hook_key.h"

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
}			t_player;

t_point	player_direction(const t_keys keys);
void	player_move(t_player *player, t_point direction,
			char **map, t_point mapsize);
void	player_rotate(t_player *player, t_mouse mouse, const t_keys keys);

#endif
