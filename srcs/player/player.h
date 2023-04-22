#ifndef PLAYER_H
# define PLAYER_H

# include "point.h"
# include "hook_mouse.h"
# include "hook_key.h"

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
	t_point	plane;
}			t_player;

t_point	player_direction(const t_keys keys);
void	player_move(t_player *player, const t_point direction);
void	player_rotate(t_point *dir, const t_mouse mouse, const t_keys keys);

#endif