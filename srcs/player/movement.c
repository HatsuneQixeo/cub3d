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

#include "libft.h"
#include "player.h"

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
	const size_t		len = sizeof(key_vectors) / sizeof(key_vectors[0]);

	return (keys_to_vector(keys, key_vectors, len));
}

/*
	Bug: Rounds incorrectly if the player speed is too high
	Bug: Go through walls if the player speed is too high

	Why not fix it? Not that this game has any speed boost effect anyway.
*/
static t_point	vector_collision(const t_point start, const t_point vector,
			char **map, const t_point mapsize)
{
	const t_point	offset = point_upscale(point_sign(vector), -.000001);
	t_point			end;

	end.x = ft_dminmax(0, start.x + vector.x, mapsize.x - 1);
	end.y = ft_dminmax(0, start.y + vector.y, mapsize.y - 1);
	if (map[(int)start.y][(int)end.x] == '1')
		end.x = roundf(start.x) + offset.x;
	if (map[(int)end.y][(int)start.x] == '1')
		end.y = roundf(start.y) + offset.y;
	return (end);
}

void	player_move(t_player *player, const t_point direction,
			char **map, const t_point mapsize)
{
	const t_point	rotate = point_rotate(direction, point_angle(player->dir));
	t_point			vector;

	if (rotate.x == 0 && rotate.y == 0)
		return ;
	else if (rotate.x != 0 && rotate.y != 0)
		vector = point_upscale(rotate, .05);
	else
		vector = point_upscale(rotate, .1);
	// vector = point_upscale(vector, 1);
	player->pos = vector_collision(player->pos, vector, map, mapsize);
}

void	player_rotate(t_player *player, const t_mouse mouse, const t_keys keys)
{
	const double	key_direction = ((keys[Key_Right] == Press)
			- (keys[Key_Left] == Press)) * 0.039;
	// const double	mouse_speed = (mouse.pos.x - mouse.prev_pos.x) * (.00831 * .39);
	const double	mouse_speed = 0;
	const double	rotation = key_direction + mouse_speed;

	player->dir = point_rotate(player->dir, rotation);
	(void)mouse;
}
