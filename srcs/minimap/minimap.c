#include "minimap.h"

void	image_draw_image(t_image *dst, const t_image *src, const t_point pos)
{
	const t_point	offset = point_apply(src->putoffset, trunc);
	const t_point	begin = {
		.x = ft_dmax(0, pos.x + offset.x),
		.y = ft_dmax(0, pos.x + offset.y)
	};
	const t_point	end = {
		.x = ft_dmin(dst->size.x, pos.x + offset.x + src->size.x),
		.y = ft_dmin(dst->size.y, pos.y + offset.y + src->size.y),
	};
	t_point			it;

	if (!(begin.x < end.x && begin.y < end.y))
		return ;
	it.y = begin.y - 1;
	while (++it.y < end.y)
	{
		it.x = begin.x - 1;
		while (++it.x < end.x)
			image_setpixel(dst, image_getpixel(src, point_sub(it, offset)), it);
	}
}
