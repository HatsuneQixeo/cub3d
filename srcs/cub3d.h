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

# define TILE_SIZE	64

typedef struct s_player
{
	t_point	pos;
	t_point	dir;
	// t_point	plane; /* ??? */
}			t_player;

/* ??? */
// typedef struct s_ray
// {
// 	double	camera_x;
// 	double	ray_dir_x;
// 	double	ray_dir_y;
// 	int		map_x;
// 	int		map_y;
// 	double	side_dist_x;
// 	double	side_dist_y;
// 	double	delta_dist_x;
// 	double	delta_dist_y;
// 	double	perp_wall_dist;
// 	int		step_x;
// 	int		step_y;
// 	int		side;
// }			t_ray;

typedef struct s_map
{
	t_point	size;
	char	**layout;
}			t_map;

typedef struct s_game
{
	t_mlx		mlx;
	t_image		screen_buffer;
	t_texture	texture;
	t_player	player;
	// t_ray		ray;
	t_keys		keys;
	t_mouse		mouse;
	t_map		map;
}			t_game;

enum e_screen_size
{
	ScreenWidth = 1280,
	ScreenHeight = 720,
	BorderWidth = ScreenWidth / 16,
	BorderHeight = ScreenHeight / 16,
	MinimapWidth = 160,
	MinimapHeight = 160,
	MnmBorderWidth = MinimapWidth / 16,
	MnmBorderHeight = MinimapHeight / 16,
};

t_point	player_vector(const t_keys keys);
void	cast_a_ray(const t_mlx mlx, const t_point player, const t_point direction);

int		hook_loop(t_game *game);

t_game	game_init(void);
void	events(t_game *game);
void	beta_screen_buffer(t_image screen_buffer);

#endif
