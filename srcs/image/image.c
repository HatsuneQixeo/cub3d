/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

static t_colour	*image_getdata(void *p_image)
{
	int	var_void;

	return ((t_colour *)mlx_get_data_addr(p_image,
			&var_void, &var_void, &var_void));
}

t_image	image_create(void *p_mlx, const t_pixelpoint size,
			t_offset putoffset_x, t_offset putoffset_y)
{
	t_image	image;

	ft_bzero(&image, sizeof(image));
	image.p_image = mlx_new_image(p_mlx, size.x, size.y);
	if (image.p_image == NULL)
		return (image);
	image.data = image_getdata(image.p_image);
	image.putoffset_x = putoffset_x;
	image.putoffset_y = putoffset_y;
	image.size = size;
	return (image);
}

/*
	Not sure if the return value is really describing anything about the error

	a file format error?
	a file error?
	a mlx error?
*/
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
	image.data = image_getdata(image.p_image);
	return (image);
}

void	image_destroy(void *p_mlx, t_image *image)
{
	mlx_destroy_image(p_mlx, image->p_image);
	ft_bzero(image, sizeof(*image));
}
