/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:47 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef HOOK_MOUSE_H
# define HOOK_MOUSE_H

# include "hook.h"
# include "point.h"

typedef struct s_mouse
{
	t_point	pos;
	t_point	prev_pos;
	t_point	press;
	int		focus;
}			t_mouse;

int	hook_mouse_move(int x, int y, t_mouse *mouse);

#endif
