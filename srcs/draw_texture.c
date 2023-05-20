#include "cub3d.h"

typedef struct s_normslave
{
	double			line_height;
	unsigned int	image_x;
	unsigned int	screen_x;
}			t_normslave;

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

static int	get_image_x(const t_image *image, const t_ray *ray,
			const t_point player_pos)
{
	const t_point	distance = point_upscale(ray->direction, ray->magnitude);
	const t_point	hit = point_add(player_pos, distance);
	const t_point	off = point_sub(hit, point_apply(hit, trunc));
	const double	x = (double []){off.y, off.x}[ray->side == SideVertical];

	if ((ray->side == SideHorizontal && ray->direction.x < 0)
		|| (ray->side == SideVertical && ray->direction.y > 0))
		return ((1 - x) * image->size.x);
	else
		return (x * image->size.x);
}

static void	draw_line(t_image *screen_buffer, const t_image *image,
			const t_normslave var)
{
	const double	image_step = image->size.y / var.line_height;
	const double	screen_end_y = trunc(ft_dmin(ScreenHeight,
				(var.line_height + ScreenHeight) / 2));
	double			screen_y;
	double			it_img_y;
	t_colour		colour;

	screen_y = ft_dmax(0, (ScreenHeight - var.line_height) / 2);
	it_img_y = (screen_y + ((var.line_height - ScreenHeight) / 2)) * image_step;
	if (isnan(it_img_y))
		it_img_y = 0;
	screen_y = trunc(screen_y - 1);
	while (++screen_y < screen_end_y)
	{
		colour = image_getpixel(image, (t_point){
				.x = var.image_x,
				.y = ft_min(it_img_y, image->size.y - 1)
			});
		image_setpixel(screen_buffer, colour, (t_point){
			.x = var.screen_x,
			.y = screen_y
		});
		it_img_y += image_step;
	}
}

void	render_wall(t_image *screen_buffer, const t_rays rays,
			const t_wall_textures walls, const t_map *map)
{
	unsigned int	i;
	const t_ray		*ray;
	const t_image	*image;

	i = -1;
	while (++i < ScreenWidth)
	{
		ray = &rays[(int)(i * ((double)ray_amount / ScreenWidth))];
		image = &walls[get_texture_index(ray->direction, ray->side)];
		draw_line(screen_buffer, image, (t_normslave){
			.line_height = ScreenHeight / ray->magnitude,
			.image_x = get_image_x(image, ray, map->player.pos),
			.screen_x = i
		});
	}
}

void	render_door(t_image *screen_buffer, const t_rays rays,
			const t_image *animation, const t_map *map)
{
	unsigned int	i;
	const t_door	*door;
	const t_ray		*ray;
	const t_image	*image;

	i = -1;
	while (++i < ScreenWidth)
	{
		ray = &rays[(int)(i * ((double)ray_amount / ScreenWidth))];
		if (!cubmap_isdoor(map, ray->hit))
			continue ;
		door = *(t_door **)ft_aafind((void **)map->arr_doors,
				&ray->hit, cmp_doorpos);
		image = &animation[door->animation_index];
		draw_line(screen_buffer, image, (t_normslave){
			.line_height = ScreenHeight / ray->magnitude,
			.image_x = get_image_x(image, ray, map->player.pos),
			.screen_x = i
		});
	}
}
