#include "cub3d.h"

void	render_background(t_image *screen_buffer,
			const t_colour ceiling, const t_colour floor)
{
	image_draw_rectangle(screen_buffer, ceiling,
		(t_point){.x = 0, .y = 0},
		(t_point){.x = ScreenWidth, .y = ScreenHeight / 2});
	image_draw_rectangle(screen_buffer, floor,
		(t_point){.x = 0, .y = ScreenHeight / 2},
		(t_point){.x = ScreenWidth, .y = ScreenHeight});
}

void	render(t_game *game)
{
	render_background(&game->screen_buffer,
		game->texture.colour_ceiling, game->texture.colour_floor);
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
