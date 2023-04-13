/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:47 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_MOUSE_H
# define HOOK_MOUSE_H

# include "hook.h"
# include "point.h"

// enum e_mouse_buttons_index
// {
// 	MouseLeft,
// 	MouseRight,
// 	MouseMiddle,
// 	MouseScrollUp,
// 	MouseScrollDown,
// 	mouse_buttons_count
// };

// typedef int	t_mouse_buttons[mouse_buttons_count];

typedef struct s_mouse
{
	t_point		pos;
	t_point		prev_pos;
	t_point		press;
	// t_mouse_buttons	buttons;
	int			left_click;
}			t_mouse;

int	hook_mouse_click(int button, int x, int y, t_mouse *mouse);
int	hook_mouse_release(int button, int x, int y, t_mouse *mouse);
int	hook_mouse_move(int x, int y, t_point *mouse_pos);

#endif
