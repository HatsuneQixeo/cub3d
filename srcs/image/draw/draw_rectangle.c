#include "image.h"

void	image_draw_rectangle(t_image *image, const t_colour colour,
				const t_point start, const t_point end)
{
	t_point	it;

	it.y = start.y - 1;
	while (++it.y < end.y)
	{
		it.x = start.x - 1;
		while (++it.x < end.x)
			image_setpixel(image, colour, it);
	}
}
