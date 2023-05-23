/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:04:57 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "liblinked_list.h"

t_list	*ft_lstmap(const t_list *lst_src, t_ftmap ft_map, t_ftdel del)
{
	t_list	*lst_map;
	t_list	**it;

	lst_map = NULL;
	it = &lst_map;
	while (lst_src != NULL)
	{
		*it = ft_lstnew(ft_map(lst_src->content));
		if (*it == NULL || (*it)->content == NULL)
		{
			ft_lstclear(&lst_map, del);
			return (NULL);
		}
		it = &(*it)->next;
		lst_src = lst_src->next;
	}
	return (lst_map);
}
