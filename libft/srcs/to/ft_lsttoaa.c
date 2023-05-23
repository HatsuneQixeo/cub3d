/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoaa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:49:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libto.h"

int	ft_lstaccumulate_nonnull(const t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i += lst->content != NULL;
		lst = lst->next;
	}
	return (i);
}

/**
 * @brief Maybe a ft_lsttoaa_reverse for a reversed linked list?
 * Example where there would be reversed linked list:
 * Used ft_lstadd_front instead of ft_lstadd_back in loop
 * for linear time complexity
 *
 * A function for reversing the 2darray would work too
 */

void	**ft_lsttoaa(const t_list *lst, t_ftmap ft_map, t_ftdel del)
{
	void	**aa;
	void	*content;
	int		y;

	aa = malloc(sizeof(void *) * (ft_lstaccumulate_nonnull(lst) + 1));
	if (aa == NULL)
		return (NULL);
	y = 0;
	while (lst != NULL)
	{
		content = lst->content;
		lst = lst->next;
		if (content == NULL)
			continue ;
		aa[y] = ft_map(content);
		if (aa[y++] == NULL)
		{
			ft_aaclear(aa, del);
			return (NULL);
		}
	}
	aa[y] = NULL;
	return (aa);
}

void	**ft_lsttoaa_clear(t_list **lst)
{
	void	**aa;

	aa = ft_lsttoaa(*lst, map_copy, NULL);
	ft_lstclear(lst, NULL);
	return (aa);
}
