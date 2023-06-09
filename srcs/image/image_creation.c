/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "image.h"
#include <errno.h>

static t_colour	*image_getdata(void *p_image)
{
	int	var_void;

	return ((t_colour *)mlx_get_data_addr(p_image,
			&var_void, &var_void, &var_void));
}

t_image	image_create(void *p_mlx, const t_point size, const t_point putoffset)
{
	t_image	image;

	ft_bzero(&image, sizeof(image));
	image.p_image = mlx_new_image(p_mlx, size.x, size.y);
	if (!image_good(&image))
		return (image);
	image.data = image_getdata(image.p_image);
	image.putoffset = putoffset;
	image.size = size;
	return (image);
}

t_image	image_dup(void *p_mlx, const t_image *src)
{
	t_image	image;

	image = image_create(p_mlx, src->size, src->putoffset);
	if (image.data == NULL)
		return (image);
	ft_memcpy(image.data, src->data,
		(image.size.y * image.size.x) * sizeof(t_colour));
	return (image);
}

t_image	image_readxpm(void *p_mlx, const char *path,
			t_offset putoffset_x, t_offset putoffset_y)
{
	t_image	image;
	int		width;
	int		height;

	ft_bzero(&image, sizeof(image));
	if (cmp_strsuffix(path, ".xpm"))
	{
		errno = ENOEXEC;
		return (image);
	}
	image.p_image = mlx_xpm_file_to_image(p_mlx, (char *)path, &width, &height);
	if (!image_good(&image))
		return (image);
	image.size = (t_point){.x = width, .y = height};
	image.data = image_getdata(image.p_image);
	image.putoffset = (t_point){
		.x = putoffset_x(image.size.x),
		.y = putoffset_y(image.size.y)
	};
	return (image);
}

t_image	image_crop(void *p_mlx, const t_image *src,
			const t_point start, const t_point end)
{
	const t_point	size = point_sub(end, start);
	t_image			image;
	t_point			it;

	image = image_create(p_mlx, size, (t_point){0, 0});
	if (!image_good(&image))
		return (image);
	it.y = start.y - 1;
	while (++it.y < end.y)
	{
		it.x = start.x - 1;
		while (++it.x < end.x)
			image_setpixel(&image, image_getpixel(src, it),
				point_sub(it, start));
	}
	return (image);
}
