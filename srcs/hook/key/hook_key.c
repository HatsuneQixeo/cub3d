/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hook_key.h"
#include "libft.h"

#ifndef DEBUG_KEY
# define DEBUG_KEY	0
#endif

typedef struct s_key_pair
{
	int	keycode;
	int	key_index;
}			t_key_pair;

static void	debug_key(const char *format, ...)
{
	va_list	args;

	if (!DEBUG_KEY)
		return ;
	va_start(args, format);
	ft_printf_core(STDERR_FILENO, format, args);
	va_end(args);
}

static int	find_key(unsigned int i, const void *arr_key_pair,
				const void *p_keycode)
{
	const t_key_pair	*key_pair = arr_key_pair;

	return (key_pair[i].keycode == *(const int *)p_keycode);
}

static int	key_action(t_keys keys, const int keycode,
				const enum e_input key_action)
{
	const t_key_pair	key_pairs[] = {
	{.keycode = 13, .key_index = Key_W},
	{.keycode = 0, .key_index = Key_A},
	{.keycode = 1, .key_index = Key_S},
	{.keycode = 2, .key_index = Key_D},
	{.keycode = 53, .key_index = Key_ESC},
	{.keycode = 123, .key_index = Key_Left},
	{.keycode = 124, .key_index = Key_Right},
	};
	const size_t		len = (sizeof(key_pairs) / sizeof(key_pairs[0]));
	const size_t		find = ft_arrfind(key_pairs, len, find_key, &keycode);

	if (find == NOTFOUND)
		debug_key(" undefined key: %d\n", keycode);
	else
	{
		keys[key_pairs[find].key_index] = key_action;
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
