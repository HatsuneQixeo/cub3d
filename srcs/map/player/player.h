#ifndef PLAYER_H
# define PLAYER_H

# include "libft.h"
# include "point.h"
# include "cubmap.h"
# include "ray.h"
/* Would be getting these's hook off I think */
# include "hook_mouse.h"
# include "hook_key.h"

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
	t_point	target;
}			t_player;

t_point	player_direction(const t_keys keys);
void	player_move(t_player *player, t_point direction, const t_map *map);
void	player_rotate(t_player *player, t_mouse mouse, const t_keys keys);
void	player_target(t_player *player, const t_map *map);

#endif
