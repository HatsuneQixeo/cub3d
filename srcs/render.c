#include "cub3d.h"

static void	render_background(t_image *screen_buffer,
			const t_colour ceiling, const t_colour floor)
{
	const unsigned int	len = screen_buffer->size.y * screen_buffer->size.x;
	const unsigned int	half = len / 2;

	ft_intset((int *)screen_buffer->data, half, ceiling);
	ft_intset((int *)screen_buffer->data + half, half + (len & 0b1), floor);
}

typedef void	(*t_ftrender)(t_image *screen_buffer, const t_rays rays,
			const t_image *images, const t_map *map);

static void	render_core(const t_ftrender ft_render, t_game *game,
			const t_image *images, const char *target)
{
	screen_rays(game->rays, &game->map, target);
	ft_render(&game->screen_buffer, game->rays, images, &game->map);
	image_put(game->mlx, &game->screen_buffer, (t_point){0, 0});
}

void	render(t_game *game)
{
	TIME("background", render_background(&game->screen_buffer,
		game->texture.colour_ceiling, game->texture.colour_floor));
	/* Raycasting */
	TIME("render total",
		/* put wall */
		{
			TIME("raycast_wall", screen_rays(game->rays, &game->map, set_wall()));
			TIME("render_wall ", render_wall(&game->screen_buffer, game->rays, game->texture.walls, &game->map));
			TIME("put_wall    ", image_put(game->mlx, &game->screen_buffer, (t_point){0, 0}));
			BENCHMARK_MSG();
		}
		/* put door */
		{
			TIME("raycast_door", screen_rays(game->rays, &game->map, set_door()));
			TIME("render_door ", render_door(&game->screen_buffer, game->rays, game->texture.door_animation, &game->map));
			TIME("put_door    ", image_put(game->mlx, &game->screen_buffer, (t_point){0, 0}));
			BENCHMARK_MSG();
		}
		/* put door */
		{
			TIME("raycast_any ", screen_rays(game->rays, &game->map, set_any()));
			TIME("render_any  ", render_door(&game->screen_buffer, game->rays, game->texture.door_animation, &game->map));
			TIME("put_any     ", image_put(game->mlx, &game->screen_buffer, (t_point){0, 0}));
			BENCHMARK_MSG();
		}
	);
}
