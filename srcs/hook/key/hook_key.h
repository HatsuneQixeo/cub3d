/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_KEY_H
# define HOOK_KEY_H

# include "hook.h"

/*
	In case you wonder why key_count is in lower snake case,
	norminette has bugs with having capital letters in typedef
*/
enum e_keys_index
{
	Key_W,
	Key_A,
	Key_S,
	Key_D,
	Key_ESC,
	Key_Left,
	Key_Right,
	key_count
};

/*
	One interesting things with typedef from enum e_keys_index
	there will actually be compile error with assigning from different enum type
*/
typedef enum e_input	t_keys[key_count];

int	hook_key_press(const int keycode, t_keys keys);
int	hook_key_release(const int keycode, t_keys keys);

#endif
