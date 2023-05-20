#include "cubmap.h"

void	player_target(t_player *player, const t_map *map)
{
	const t_ray	ray = raycast(map, player->pos, player->dir, set_any());
	t_point		vector;

	if (ray.magnitude < point_magnitude(player->dir))
		vector = point_upscale(ray.direction, ray.magnitude + 0.000001);
	else
		vector = player->dir;
	player->target = point_apply(point_add(player->pos, vector), trunc);
}
