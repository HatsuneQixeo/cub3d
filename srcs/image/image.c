#include "image.h"

unsigned int	size_area(const t_size size)
{
	return (size.x * size.y);
}

t_image	image_create(void *p_mlx, const t_size size)
{
	t_image	image;

	ft_bzero(&image, sizeof(image));
	image.p_image = mlx_new_image(p_mlx, size.x, size.y);
	if (image.p_image == NULL)
		return (image);
	image.data = (t_colour *)mlx_get_data_addr(image.p_image,
			(int[1]){0}, (int[1]){0}, (int[1]){0});
	image.size = size;
	return (image);
}

t_image	image_readxpm(void *p_mlx, const char *path)
{
	t_image	image;

	ft_bzero(&image, sizeof(image));
	if (cmp_strsuffix(path, ".xpm"))
		return (image);
	image.p_image = mlx_xpm_file_to_image(p_mlx, (char *)path,
			&image.size.x, &image.size.y);
	if (image.p_image == NULL)
		return (image);
	image.data = (t_colour *)mlx_get_data_addr(image.p_image,
			(int[1]){0}, (int[1]){0}, (int[1]){0});
	return (image);
}

void	image_destroy(void *p_mlx, t_image *image)
{
	mlx_destroy_image(p_mlx, image->p_image);
	ft_bzero(image, sizeof(*image));
}

void	image_put(t_mlx mlx, t_image *p_image, t_size pos)
{
	mlx_put_image_to_window(mlx.p_mlx, mlx.p_win, p_image->p_image, 0, 0);
}
