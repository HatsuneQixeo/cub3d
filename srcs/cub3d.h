/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "point.h"
# include "hook_key.h"
# include "hook_mouse.h"
# include "texture.h"
# include "player.h"
# include "cubmap.h"

# define CELL_SIZE	64

typedef struct s_game
{
	t_mlx		mlx;
	t_image		screen_buffer;
	t_texture	texture;
	t_player	player;
	t_keys		keys;
	t_mouse		mouse;
	t_map		map;
}			t_game;

enum e_screen_size
{
	// ScreenWidth = 1000,
	ScreenWidth = 1280,
	ScreenHeight = 720,
	ScreenBorderWidth = ScreenWidth / 16,
	ScreenBorderHeight = ScreenHeight / 16,
};

enum e_minimap_size
{
	MapCellSize = CELL_SIZE / 2,
	MinimapScale = 7,
	MinimapLength = MapCellSize * MinimapScale,
};

void	cast_a_ray(const t_mlx mlx, const t_point player, const t_point vector);

int		hook_loop(t_game *game);

t_game	game_init(void);
void	events(t_game *game);
void	beta_screen_buffer(t_image screen_buffer);

#endif
