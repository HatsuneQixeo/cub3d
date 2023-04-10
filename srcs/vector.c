/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/10 22:58:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"
#include "hook_key.h"
#include "libft.h"

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
		{
			vector.x += arr_key_vectors[i].vector.x;
			vector.y += arr_key_vectors[i].vector.y;
		}
	}
	return (vector);
}

t_point	player_vector(const t_keys keys)
{
	const double		move_speed = 1;
	const t_key_vector	key_vectors[] = {
	{.key_index = Key_W, .vector = {.x = 00, .y = -move_speed}},
	{.key_index = Key_A, .vector = {.x = -(move_speed / 2), .y = 00}},
	{.key_index = Key_S, .vector = {.x = 00, .y = +(move_speed / 2)}},
	{.key_index = Key_D, .vector = {.x = +(move_speed / 2), .y = 00}},
	};
	const size_t		len = sizeof(key_vectors) / sizeof(key_vectors[0]);

	return (keys_to_vector(keys, key_vectors, len));
}
