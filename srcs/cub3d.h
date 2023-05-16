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
# include "exlib.h"
# include "point.h"
# include "hook_key.h"
# include "hook_mouse.h"
# include "texture.h"
# include "player.h"
# include "cubmap.h"
# include "ray.h"
# include "minimap.h"

/* Screen */
enum e_screen_size
{
	ScreenWidth = 1280,
	ScreenHeight = 720,
};

/* Ray */
enum e_ray_amount
{
	ray_amount = ScreenWidth
};

typedef t_ray	t_rays[ray_amount];

typedef struct s_game
{
	t_mlx		mlx;
	t_image		screen_buffer;
	t_rays		rays;
	t_texture	texture;
	t_player	player;
	t_keys		keys;
	t_mouse		mouse;
	t_map		map;
}			t_game;

void	put_a_line(t_mlx mlx, t_point player, t_point vector);

void	screen_rays(t_rays rays, const t_player *player, t_map map);
void	ray_draw_texture(t_image *screen_buffer, const t_rays rays,
			const t_wall_textures walls, t_point player_pos);

int		hook_loop(t_game *game);

int		game_init(const char *path, t_game *game);
void	events(t_game *game);

int		hook_expose(t_game *game);
int		hook_loop(t_game *game);

void	cub3d_map_render(const t_game *game);

#endif
