#include "image.h"

void	image_draw_pixel(t_image *image, const t_colour colour, const t_size at)
{
	if (at.x < 0 || at.x >= image->size.x
		|| at.y < 0 || at.y >= image->size.y)
		return ;
	image->data[(at.y * image->size.x) + at.x] = colour;
}

void	image_draw_rectangle(t_image *image, const t_colour colour,
				const t_size start, const t_size end)
{
	t_size	index;

	index.y = start.y;
	while (index.y <= end.y)
	{
		index.x = start.x;
		while (index.x <= end.x)
		{
			image_draw_pixel(image, colour, index);
			index.x++;
		}
		index.y++;
	}
}

void	image_fill(t_image *image, const t_colour colour)
{
	image_draw_rectangle(image, colour, (t_size){0, 0}, image->size);
}

int	getsign(const int x)
{
	if (x > 0)
		return (1);
	else if (x < 0)
		return (-1);
	else
		return (0);
}

void	image_draw_line(t_image *image, const t_colour colour, const t_size start, const t_size end)
{
	t_size	point;
	t_size	delta;
	t_size	sign;
	t_size	error;

	delta.x = abs(end.x - start.x);
	delta.y = abs(end.y - start.y);
	sign.x = start.x < end.x ? 1 : -1;
	sign.y = start.y < end.y ? 1 : -1;
	ft_assert(delta.x != 0 || delta.y != 0, "image_draw_line: start == end");
	ft_assert(sign.x == getsign(end.x - start.x), "image_draw_line: inverted getsign X?");
	ft_assert(sign.y == getsign(end.y - start.y), "image_draw_line: inverted getsign Y?");
	error.x = delta.x - delta.y;
	error.y = 0;
	point = start;
	while (1)
	{
		image_draw_pixel(image, colour, point);
		if (point.x == end.x && point.y == end.y)
			break ;
		error.y = error.x * 2;
		if (error.y > -delta.y)
		{
			error.x -= delta.y;
			point.x += sign.x;
		}
		if (error.y < delta.x)
		{
			error.x += delta.x;
			point.y += sign.y;
		}
	}
}
