/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:05 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "hook_key.h"
#include "libft.h"

#ifndef DEBUG_KEY
# define DEBUG_KEY	0
#endif

static void	debug_key(const char *format, ...)
{
	va_list	args;

	if (!DEBUG_KEY)
		return ;
	va_start(args, format);
	ft_printf_core(STDERR_FILENO, format, args);
	va_end(args);
}

static int	find_key(unsigned int i, const void *arr_keycode,
			const void *p_keycode)
{
	const int	*arr = arr_keycode;

	return (arr[i] == *(int *)p_keycode);
}

/*
	If you're sharp,
	you probably noticed that the Key_RCtrl is defined in header but not here.

	If you're sharper,
	you would notice that it's because this function has exactly 24 lines.

	Although if I have strong reason to include it,
	I could just multiply the sizeof(t_keys) in bzero with the expression,
	but I don't.
*/
static int	key_action(t_keys keys, const int keycode,
				const enum e_input key_action)
{
	const int			key_pairs[] = {
	[Key_W] = 13,
	[Key_A] = 0,
	[Key_S] = 1,
	[Key_D] = 2,
	[Key_ESC] = 53,
	[Key_Left] = 123,
	[Key_Right] = 124,
	[Key_E] = 14,
	[Key_LCtrl] = 259,
	};
	const unsigned int	len = (sizeof(key_pairs) / sizeof(key_pairs[0]));
	const size_t		find = ft_arrfind(key_pairs, len, find_key, &keycode);

	if (find == NOTFOUND)
		debug_key(" undefined key: %d\n", keycode);
	else
	{
		if (find == Key_LCtrl)
			ft_bzero(keys, sizeof(t_keys));
		keys[find] = key_action;
		debug_key(" key: %d\n", keycode);
		return (0);
	}
	return (-1);
}

int	hook_key_press(const int keycode, t_keys keys)
{
	debug_key(ANSI_B_CYAN"Pressed"ANSI_RESET);
	return (key_action(keys, keycode, Press));
}

int	hook_key_release(const int keycode, t_keys keys)
{
	debug_key(ANSI_CYAN"Released"ANSI_RESET);
	return (key_action(keys, keycode, Release));
}
