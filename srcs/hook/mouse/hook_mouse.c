/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook_mouse.h"
#include "libft.h"

#ifndef DEBUG_BUTTON
# define DEBUG_BUTTON	0
#endif

static void	debug_button(const char *format, ...)
{
	va_list	args;

	if (!DEBUG_BUTTON)
		return ;
	va_start(args, format);
	ft_printf_core(STDERR_FILENO, format, args);
	va_end(args);
}

#if 0

typedef struct s_button_pair
{
	enum e_mouse	button;
	int				button_index;
}				t_button_pair;

int	find_button(unsigned int i, const void *arr_button_pair,
			const void *p_button)
{
	const t_button_pair	*button_pair = arr_button_pair;

	return (button_pair[i].button == *(const int *)p_button);
}

void	mouse_action(t_mouse_buttons buttons, int button,
			enum e_input mouse_action)
{
	const t_button_pair	button_pairs[] = {
	{.button = 1, .button_index = MouseLeft},
	{.button = 2, .button_index = MouseRight},
	{.button = 3, .button_index = MouseMiddle},
	{.button = 4, .button_index = MouseScrollUp},
	{.button = 5, .button_index = MouseScrollDown},
	};
	const size_t		len = (sizeof(button_pairs) / sizeof(button_pairs[0]));
	const size_t		find = ft_arrfind(button_pairs, len, find_button, &button);

	if (find == NOTFOUND)
		debug_mouse(" undefined mouse button: %d\n", button);
	else
		buttons[button_pairs[find].button_index] = mouse_action;
}
#endif

int	hook_mouse_click(int button, int x, int y, t_mouse *mouse)
{
	debug_button("mouse click: %d, x: %d, y: %d\n", button, x, y);
	if (y < 0 || button != 1)
		return (-1);
	mouse->press = (t_point){.x = x, .y = y};
	return (0);
}

int	hook_mouse_release(int button, int x, int y, t_mouse *mouse)
{
	debug_button("mouse release: %d, x: %d, y: %d\n", button, x, y);
	mouse->press = (t_point){.x = x, .y = y};
	return (0);
}

int	hook_mouse_move(int x, int y, t_mouse *mouse)
{
	mouse->prev_pos = mouse->pos;
	mouse->pos = (t_point){.x = x, .y = y};
	return (0);
}
