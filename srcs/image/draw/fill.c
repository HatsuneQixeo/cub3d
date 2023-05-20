#include "image.h"

void	image_fill(t_image *image, const t_colour colour)
{
	ft_intset((int *)image->data, image->size.x * image->size.y, colour);
}

void	image_clean(t_image *image)
{
	image_fill(image, 0xff000000);
}
