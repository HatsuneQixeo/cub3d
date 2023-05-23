/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aatolst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:54:42 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libto.h"

t_list	*ft_aatolst(void **aa, t_ftmap ft_map, t_ftdel del)
{
	t_list	*lst;
	t_list	*node;
	int		size;

	lst = NULL;
	size = ft_aasize(aa);
	while (size--)
	{
		node = ft_lstnew(ft_map(aa[size]));
		if (node == NULL || node->content == NULL)
		{
			ft_lstclear(&lst, del);
			return (NULL);
		}
		ft_lstadd_front(&lst, node);
	}
	return (lst);
}

t_list	*ft_aatolst_clear(void **aa)
{
	t_list	*lst;

	lst = ft_aatolst(aa, map_copy, NULL);
	free(aa);
	return (lst);
}
