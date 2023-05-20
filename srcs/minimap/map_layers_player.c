#include "minimap.h"

// t_point	point_clamp(const t_point point,
// 			const t_point min, const t_point max)
// {
// 	const t_point	new_point = {
// 		.x = ft_dminmax(min.x, point.x, max.x),
// 		.y = ft_dminmax(min.y, point.y, max.y),
// 	};

// 	return (new_point);
// }

// t_point	point_multiply(const t_point a, const t_point b)
// {
// 	const t_point	point = {
// 		.x = a.x * b.x,
// 		.y = a.y * b.y
// 	};

// 	return (point);
// }

// static void	layer_player_delta(t_image *layer, const t_player *player)
// {
// 	const t_point	map_pos = map_scale_point(player->pos);
// 	const t_colour	colour = colour_from_percentage(.2, .2, .2, 0);
// 	t_point			delta;
// 	t_point			end;

// 	delta = (t_point){
// 		.x = sqrt((1 + pow(player->dir.y, 2) / pow(player->dir.x, 2))),
// 		.y = sqrt((1 + pow(player->dir.x, 2) / pow(player->dir.y, 2))),
// 	};
// 	delta = map_scale_point(delta);
// 	if (player->dir.x == 0)
// 		delta.x = 0;
// 	if (player->dir.y == 0)
// 		delta.y = 0;
// 	delta = point_multiply(delta, point_sign(player->dir));
// 	end = point_add(map_pos, delta);
// 	end = point_clamp(end, (t_point){0, 0},
// 			(t_point){.x = layer->size.x - 1, .y = layer->size.y - 1});
// 	image_draw_line(layer, colour, map_pos, end);
// }

void	map_layer_player(t_image *layer, const t_player *player)
{
	const t_point	map_pos = point_apply(map_scale_point(player->pos), trunc);
	const t_colour	colour = colour_from_percentage(.2, .8, .8, .4);

	if (!point_inbound(map_pos, layer->size))
		return ;
	image_draw_line(layer, colour_from_rgba(100, 200, 200, 10),
		map_pos, point_add(map_pos, map_scale_point(player->dir)));
	image_draw_circle(layer, colour, map_pos, 9);
}
