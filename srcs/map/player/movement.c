/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubmap.h"

#ifndef COLLISION
# define COLLISION 1
#endif

typedef struct s_key_vector
{
	int		key_index;
	t_point	vector;
}			t_key_vector;

static t_point	keys_to_vector(const t_keys keys,
			const t_key_vector *arr_key_vectors, const size_t length)
{
	t_point	vector;
	size_t	i;

	ft_bzero(&vector, sizeof(vector));
	i = -1;
	while (++i < length)
	{
		if (keys[arr_key_vectors[i].key_index] == Press)
			vector = point_add(vector, arr_key_vectors[i].vector);
	}
	return (vector);
}

t_point	player_direction(const t_keys keys)
{
	const t_key_vector	key_vectors[] = {
	{.key_index = Key_W, .vector = {.x = 00, .y = -1}},
	{.key_index = Key_A, .vector = {.x = -1, .y = 00}},
	{.key_index = Key_S, .vector = {.x = 00, .y = +1}},
	{.key_index = Key_D, .vector = {.x = +1, .y = 00}},
	};
	const unsigned int	len = sizeof(key_vectors) / sizeof(key_vectors[0]);

	return (keys_to_vector(keys, key_vectors, len));
}

/*
	Bug: Rounds incorrectly if the player speed is too high
	Bug: Go through walls if the player speed is too high

	Why not fix it? Not that this game has any speed boost effect anyway.
*/
static t_point	vector_collision(const t_point start, const t_point vector,
			const t_map *map)
{
	const t_point	offset = point_upscale(point_sign(vector), -.0831);
	t_point			end;

	end.x = ft_dminmax(0, start.x + vector.x, map->size.x - 1);
	end.y = ft_dminmax(0, start.y + vector.y, map->size.y - 1);
	if (!cubmap_iswalkable(map, (t_point){.x = end.x - offset.x, .y = start.y}))
		end.x = roundf(end.x) + offset.x;
	if (!cubmap_iswalkable(map, (t_point){.x = start.x, .y = end.y - offset.y}))
		end.y = roundf(end.y) + offset.y;
	return (end);
}

void	player_move(t_player *player, const t_point direction, const t_map *map)
{
	double	scale;
	t_point	vector;

	if (direction.x == 0 && direction.y == 0)
		return ;
	else if (direction.x != 0 && direction.y != 0)
		scale = 0.5;
	else
		scale = 0.75;
	vector = point_rotate(direction, point_angle(player->dir));
	vector = point_upscale(vector, scale * 0.1);
	if (!COLLISION)
		player->pos = point_add(player->pos, vector);
	else
		player->pos = vector_collision(player->pos, vector, map);
}

void	player_rotate(t_player *player, const t_mouse mouse, const t_keys keys)
{
	/*
		Have to fix this scope things,
		this function should rotate it with given parameter as value not key press,
		that's something should be defined outside this function
	*/
	const double	key_direction = ((keys[Key_Right] == Press)
			- (keys[Key_Left] == Press)) * 0.039;
	const double	mouse_speed = (mouse.pos.x - mouse.prev_pos.x) * (.00831 * .39);
	// const double	mouse_speed = 0;
	const double	rotation = key_direction + mouse_speed;

	player->dir = point_rotate(player->dir, rotation);
	(void)mouse;
}

void	player_target(t_player *player, const t_map *map)
{
	const t_ray	ray = raycast(map, player->pos, player->dir, set_any());
	t_point		vector;

	if (ray.distance_traveled < point_magnitude(player->dir))
		vector = point_upscale(ray.direction, ray.distance_traveled + 0.000001);
	else
		vector = player->dir;
	player->target = point_apply(point_add(player->pos, vector), trunc);
}
