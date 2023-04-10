/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/10 22:58:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_KEY_H
# define HOOK_KEY_H

# include "hook.h"
# include <stdint.h>

enum e_keys_index
{
	Key_W,
	Key_A,
	Key_S,
	Key_D,
	Key_ESC,
	key_count
};

enum e_key_action
{
	Release,
	Press
};

typedef uint8_t	t_keys[key_count];

int	hook_key_press(const int keycode, t_keys keys);
int	hook_key_release(const int keycode, t_keys keys);

#endif
