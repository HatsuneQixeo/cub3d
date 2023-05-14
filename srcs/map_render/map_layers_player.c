#include "cub3d.h"

t_point	point_clamp(const t_point point, const t_point min, const t_point max)
{
	const t_point	new_point = {
		.x = ft_dminmax(min.x, point.x, max.x),
		.y = ft_dminmax(min.y, point.y, max.y),
	};

	return (new_point);
}

t_point	point_multiply(const t_point a, const t_point b)
{
	const t_point	point = {
		.x = a.x * b.x,
		.y = a.y * b.y
	};

	return (point);
}

static void	layer_player_delta(t_image *layer, const t_player *player)
{
	const t_point	map_pos = point_upscale(player->pos, MapCellSize + 1);
	const t_colour	colour = colour_from_percentage(.2, .2, .2, 0);
	t_point	delta = {
		.x = sqrt((1 + pow(player->dir.y, 2) / pow(player->dir.x, 2))),
		.y = sqrt((1 + pow(player->dir.x, 2) / pow(player->dir.y, 2))),
	};
	t_point	end;

	delta = point_upscale(delta, MapCellSize);
	if (player->dir.x == 0)
		delta.x = 0;
	if (player->dir.y == 0)
		delta.y = 0;
	delta = point_multiply(delta, point_sign(player->dir));
	end = point_add(map_pos, delta);
	end = point_clamp(end, (t_point){0, 0},
			(t_point){.x = layer->size.x - 1, .y = layer->size.y - 1});
	image_draw_line(layer, colour, map_pos, end);
}

void	map_layers_player(t_image *layer, const t_player *player)
{
	const t_point	map_pos = point_apply(point_upscale(player->pos, MapCellSize + 1), trunc);

	if (!point_inbound(map_pos, layer->size))
		return ;
	layer_player_delta(layer, player);
	image_draw_line(layer, colour_from_rgba(200, 200, 200, 10),
		map_pos, point_add(map_pos, point_upscale(player->dir, 39)));
}
