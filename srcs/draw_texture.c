#include "cub3d.h"

static enum e_wall_texture_index	get_texture_index(const t_point direction,
			const enum e_side side)
{
	if (side == SideHorizontal)
		return ((enum e_wall_texture_index []){East, West}[direction.x > 0]);
	else if (side == SideVertical)
		return ((enum e_wall_texture_index []){South, North}[direction.y > 0]);
	else if (side != SideUnknown)
		ft_assert(0, "get_texture_index: Invalid side");
	return (Invalid);
}

static int	get_image_x(const t_image *image, const t_ray ray,
			const t_point player_pos)
{
	const t_point	dist = point_upscale(ray.direction, ray.distance_traveled);
	const t_point	hit = point_add(player_pos, dist);
	const t_point	offset = point_sub(hit, point_round(hit, trunc));
	const double	wall_x = (double []){offset.y, offset.x}[ray.side == SideVertical];
	const int		image_x = wall_x * image->size.x;

	if ((ray.side == SideHorizontal && ray.direction.x < 0)
		|| (ray.side == SideVertical && ray.direction.y > 0))
		return ((image->size.x - 1) - image_x);
	else
		return (image_x);
}

static void	draw_line(t_image *screen_buffer, const t_image *image,
			const double line_height, const unsigned int image_x, const unsigned int buffer_x)
{
	const double	image_step = (image->size.y / line_height);
	const double	screen_end_y = ft_dmin(ScreenHeight,
			(line_height + ScreenHeight) / 2);
	double			screen_y;
	double			it_img_y;

	screen_y = ft_dmax(0, (ScreenHeight - line_height) / 2);
	it_img_y = (screen_y + ((line_height - ScreenHeight) / 2)) * image_step;
	if (isnan(it_img_y))
		it_img_y = 0;
	screen_y--;
	while (++screen_y < screen_end_y)
	{
		const t_colour	colour = image_getpixel(image, (t_point){.x = image_x, .y = trunc(it_img_y)});

		image_setpixel(screen_buffer, colour, (t_point){.x = buffer_x, .y = screen_y});
		it_img_y += image_step;
	}
}

void	ray_draw_texture(t_image *screen_buffer, const t_rays rays,
			const t_wall_textures walls, const t_point player_pos)
{
	unsigned int	i;

	i = -1;
	while (++i < ScreenWidth)
	{
		const unsigned int	i_ray = i * ((double)ray_amount / ScreenWidth);
		const t_ray			ray = rays[i_ray];
		const t_image		*image = &walls[get_texture_index(ray.direction, ray.side)];
		const double		line_height = ScreenHeight / ray.distance_traveled;
		const int			image_x = get_image_x(image, ray, player_pos);

		draw_line(screen_buffer, image, line_height, image_x, i);
	}
}
