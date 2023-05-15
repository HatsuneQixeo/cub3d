#include "cub3d.h"

static enum e_wall_texture_index	get_texture_index(const t_point direction,
			const enum e_side side)
{
	if (side == SideHorizontal)
		return ((enum e_wall_texture_index []){East, West}[direction.x > 0]);
	else if (side == SideVertical)
		return ((enum e_wall_texture_index []){South, North}[direction.y > 0]);
	ft_assert(side == SideUnknown, "get_texture_index: Invalid side");
	return (Invalid);
}

static int	get_image_x(const t_image *image, const t_ray ray,
			const t_point player_pos)
{
	const t_point	dist = point_upscale(ray.direction, ray.distance_traveled);
	const t_point	hit = point_add(player_pos, dist);
	const t_point	offst = point_sub(hit, point_apply(hit, trunc));
	const double	x = (double []){offst.y, offst.x}[ray.side == SideVertical];

	if ((ray.side == SideHorizontal && ray.direction.x < 0)
		|| (ray.side == SideVertical && ray.direction.y > 0))
		return ((1 - x) * image->size.x);
	else
		return (x * image->size.x);
}

static void	draw_line(t_image *screen_buffer, const t_image *image,
			const double line_height, const unsigned int image_x,
			const unsigned int screen_x)
{
	const double	image_step = image->size.y / line_height;
	const double	screen_end_y = trunc(ft_dmin(ScreenHeight,
				(line_height + ScreenHeight) / 2));
	double			screen_y;
	double			it_img_y;

	screen_y = ft_dmax(0, (ScreenHeight - line_height) / 2);
	it_img_y = (screen_y + ((line_height - ScreenHeight) / 2)) * image_step;
	if (isnan(it_img_y))
		it_img_y = 0;
	screen_y = trunc(screen_y - 1);
	while (++screen_y < screen_end_y)
	{
		const t_colour	colour = image_getpixel(image, (t_point){
				.x = image_x,
				.y = trunc(it_img_y) - (it_img_y >= image->size.y)
			});

		image_setpixel(screen_buffer, colour, (t_point){
			.x = screen_x,
			.y = screen_y
		});
		it_img_y += image_step;
	}
}

void	ray_draw_texture(t_image *screen_buffer, const t_rays rays,
			const t_wall_textures walls, const t_point player_pos)
{
	unsigned int	i;
	t_ray			ray;
	const t_image	*image;
	double			line_height;
	int				image_x;

	i = -1;
	while (++i < ScreenWidth)
	{
		ray = rays[(int)(i * ((double)ray_amount / ScreenWidth))];
		image = &walls[get_texture_index(ray.direction, ray.side)];
		line_height = ScreenHeight / ray.distance_traveled;
		image_x = get_image_x(image, ray, player_pos);
		draw_line(screen_buffer, image, line_height, image_x, i);
	}
}
