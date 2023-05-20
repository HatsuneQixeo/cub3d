#include "cub3d.h"

void	render_background(t_image *screen_buffer,
			const t_colour ceiling, const t_colour floor)
{
	const unsigned int	len = screen_buffer->size.y * screen_buffer->size.x;
	const unsigned int	half = len / 2;

	ft_intset((int *)screen_buffer->data, half, ceiling);
	ft_intset((int *)screen_buffer->data + half, half + (len & 0b1), floor);
}

void	render(t_game *game)
{
	TIME("background", render_background(&game->screen_buffer,
		game->texture.colour_ceiling, game->texture.colour_floor));
	/* Raycasting */
	TIME("render total",
		TIME("raycast", screen_rays(game->rays, &game->map, set_wall()));
		TIME("draw   ", render_wall(&game->screen_buffer, game->rays, game->texture.walls, &game->map));
		TIME("put    ", image_put(game->mlx, &game->screen_buffer, (t_point){0, 0}));
		/* put door */
		{
			TIME("raycast", screen_rays(game->rays, &game->map, set_door()));
			TIME("draw   ", render_door(&game->screen_buffer, game->rays, game->texture.door_animation, &game->map));
			TIME("put    ", image_put(game->mlx, &game->screen_buffer, (t_point){0, 0}));
		}
		/* put door */
		{
			TIME("raycast", screen_rays(game->rays, &game->map, set_any()));
			TIME("draw   ", render_door(&game->screen_buffer, game->rays, game->texture.door_animation, &game->map));
			TIME("put    ", image_put(game->mlx, &game->screen_buffer, (t_point){0, 0}));
		}
	);
}
