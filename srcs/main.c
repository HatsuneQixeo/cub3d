/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	display_mouse(const t_mouse mouse)
{
	static int	custom_cursor;
	const int	in_screen = (unsigned int)mouse.pos.x < ScreenWidth
		&& (unsigned int)mouse.pos.y < ScreenHeight;

	if (in_screen != custom_cursor)
	{
		custom_cursor = in_screen;
		(int (*[])(void)){mlx_mouse_show, mlx_mouse_hide}[custom_cursor]();
	}
	return (custom_cursor);
}

void	mouse_focus(void *p_win, t_mouse *mouse, const int focus)
{
	const t_point	screen_center = {
		.x = ScreenWidth / 2,
		.y = ScreenHeight / 2
	};

	if (mouse->focus == focus)
		return ;
	mouse->focus = focus;
	mlx_mouse_move(p_win, screen_center.x, screen_center.y);
	mouse->pos = screen_center;
}

/*
	Originally made because a gif conversion seems to have missing pixel.
	My deduction is because certain gif image default into transparent
	if the pixel is the same as the last image,
	probably did so for optimisation purpose?
*/
// void	image_copy_opaque(t_image *dst, const t_image *src)
// {
// 	unsigned int		i;
// 	const unsigned int	len = dst->size.x * dst->size.y;

// 	i = -1;
// 	while (++i < len)
// 		if (colour_getmask(src->data[i], ValueA) != 0xff)
// 			dst->data[i] = src->data[i];
// }

// ft_printf("くるり廻る廻る廻る世界\n");
int	hook_loop(t_game *game)
{
	if (game->keys[Key_ESC] == Press)
		hook_button_close();
	mouse_focus(game->mlx.p_win, &game->mouse, game->keys[Key_LCtrl] != Press
		&& game->keys[Key_RCtrl] != Press);
	mlx_clear_window(game->mlx.p_mlx, game->mlx.p_win);
	update(game);
	render(game);
	cub3d_map_render(game);
	if (display_mouse(game->mouse))
		image_put(game->mlx, &game->texture.mouse_icon, game->mouse.pos);
	return (0);
}

int	cub3d(const char *map_path)
{
	t_game	game;

	if (cmp_strsuffix(map_path, ".cub"))
		return (!!ft_dprintf(2, "Invalid File extension: %s\n", map_path));
	ft_bzero(&game, sizeof(t_game));
	if (game_init(map_path, &game) == -1)
		exit(1);
	mlx_loop(game.mlx.p_mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (!!ft_putendl_fd("usage: cub3d <map>", 2));
	return (cub3d(argv[1]));
}
