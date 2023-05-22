/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "element.h"
#include "texture.h"
#include <string.h>
#include <errno.h>

int	get_environment_colour(t_element_table element_table,
		t_colour *ceiling, t_colour *floor);
int	check_table(const char *idx_table[], unsigned int length,
		t_element_table element_table);

static t_list	*read_image(void *p_mlx, const char *path, t_image *image)
{
	*image = image_readxpm(p_mlx, path, putoffset_default, putoffset_default);
	if (image->p_image == NULL)
		return (ft_lstnew(ft_strmerge("%s: %s", strerror(errno), path)));
	else
		return (NULL);
}

static int	read_walls(void *p_mlx, t_element_table element_table,
			t_wall_textures walls)
{
	const char	*paths[] = {
	[North] = ((t_element *)element_table[IdxElemNorth]->content)->properties,
	[East] = ((t_element *)element_table[IdxElemEast]->content)->properties,
	[South] = ((t_element *)element_table[IdxElemSouth]->content)->properties,
	[West] = ((t_element *)element_table[IdxElemWest]->content)->properties,
	};
	t_list		*lst_err;

	lst_err = NULL;
	ft_lstadd_back(&lst_err, read_image(p_mlx, paths[North], &walls[North]));
	ft_lstadd_back(&lst_err, read_image(p_mlx, paths[East], &walls[East]));
	ft_lstadd_back(&lst_err, read_image(p_mlx, paths[South], &walls[South]));
	ft_lstadd_back(&lst_err, read_image(p_mlx, paths[West], &walls[West]));
	if (lst_err == NULL)
		return (0);
	ft_putendl_fd("Error", 2);
	ft_lstiter(lst_err, iter_puterrendl);
	ft_lstclear(&lst_err, free);
	return (-1);
}

int	find_str(const unsigned int i, const void *strlist, const void *ref)
{
	const char	**arr = (const char **)strlist;

	return (!ft_strcmp(arr[i], ref));
}

static void	extract_texture(const char *idx_table[], const unsigned int length,
			const t_list *lst_element, t_element_table element_table)
{
	t_element	*ele;
	size_t		find;

	while (lst_element != NULL)
	{
		ele = lst_element->content;
		find = ft_arrfind(idx_table, length, find_str, ele->identifier);
		if (find == NOTFOUND)
			ft_lstadd_back(&element_table[IdxElemUnknown], ft_lstnew(ele));
		else
			ft_lstadd_back(&element_table[find], ft_lstnew(ele));
		lst_element = lst_element->next;
	}
}

int	cubmap_parse_texture(void *p_mlx, const t_list *lst_elements,
			t_texture *texture)
{
	const char			*idx_table[] = {
	[IdxElemNorth] = "NO",
	[IdxElemEast] = "EA",
	[IdxElemSouth] = "SO",
	[IdxElemWest] = "WE",
	[IdxElemFloor] = "F",
	[IdxElemCeiling] = "C"
	};
	const unsigned int	length = (sizeof(idx_table) / sizeof(idx_table[0]));
	t_element_table		element_table;
	int					status;

	ft_bzero(element_table, sizeof(element_table));
	extract_texture(idx_table, length, lst_elements, element_table);
	status = 0;
	if (check_table(idx_table, length, element_table) == -1)
		status = -1;
	else if (get_environment_colour(element_table,
			&texture->colour_ceiling, &texture->colour_floor) < 0)
		status = -1;
	else if (read_walls(p_mlx, element_table, texture->walls) == -1)
		status = -1;
	ft_aaiteri(element_table, iteri_lstclear_shallow);
	return (status);
}
