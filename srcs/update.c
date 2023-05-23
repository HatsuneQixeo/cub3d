/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

static void	door_iteri_update(const unsigned int i, void *arr_door)
{
	t_door **const	aa = arr_door;
	t_door *const	door = aa[i];

	if (door->step == 0)
		return ;
	door->animation_index += door->step;
	door->is_open = (door->animation_index == door->animation_amount - 1);
	if (door->animation_index == 0
		|| door->animation_index == door->animation_amount - 1)
		door->step = 0;
}

		// if ((*it_door)->is_open)
static void	map_update(t_map *map)
{
	t_door	**it_door;
	t_point	pos;

	it_door = map->arr_doors - 1;
	while (*++it_door != NULL)
	{
		pos = (*it_door)->pos;
		if ((*it_door)->animation_index != 0)
			map->layout[(int)pos.y][(int)pos.x] = DoorOpen;
		else
			map->layout[(int)pos.y][(int)pos.x] = DoorClose;
	}
}

static void	player_interact(const t_map *map, t_keys keys,
			const t_player player)
{
	t_door			*door;
	const t_point	pos = point_apply(player.pos, trunc);
	const t_point	target = player.target;

	if (keys[Key_E] == Release)
		return ;
	keys[Key_E] = Release;
	if (!cubmap_isdoor(map, target)
		|| (pos.x == target.x && pos.y == target.y))
		return ;
	door = *(t_door **)ft_aafind((void **)map->arr_doors, &target, cmp_doorpos);
	if (door->step != 0)
		door->step *= -1;
	else if (door->is_open)
		door->step = -1;
	else
		door->step = 1;
}

		// * (M_PI / 180) * 0.39;
static double	input_angle(void *p_win, t_mouse *mouse, const t_keys keys)
{
	const t_point	screen_center = {
		.x = ScreenWidth / 2,
		.y = ScreenHeight / 2
	};
	const double	key_direction = ((keys[Key_Right] == Press)
			- (keys[Key_Left] == Press)) * 0.039;
	const double	mouse_speed = (mouse->pos.x - mouse->prev_pos.x)
		* (.0831 * .39 * .39 * .39);

	if (!mouse->focus)
		return (key_direction);
	mlx_mouse_move(p_win, screen_center.x, screen_center.y);
	mouse->prev_pos = screen_center;
	mouse->pos = screen_center;
	return (key_direction + mouse_speed);
}

void	update(t_game *game)
{
	game->map.player.dir = point_rotate(game->map.player.dir,
			input_angle(game->mlx.p_win, &game->mouse, game->keys));
	player_move(&game->map.player, player_getvector(game->keys), &game->map);
	player_target(&game->map.player, &game->map);
	player_interact(&game->map, game->keys, game->map.player);
	ft_aaiteri(game->map.arr_doors, door_iteri_update);
	map_update(&game->map);
}
