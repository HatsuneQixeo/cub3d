/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:04:01 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "liblinked_list.h"

/**
 * @brief Delete the given node in linked list
 * 
 * @param lst 
 * @param node 
 * @param del 
 */
void	ft_lstremove(t_list **lst, t_list *node, t_ftdel del)
{
	t_list	*tmp;

	if (*lst == NULL)
		return ;
	else if (*lst == node)
	{
		tmp = *lst;
		*lst = tmp->next;
		ft_lstdelone(tmp, del);
	}
	else
		ft_lstremove(&(*lst)->next, node, del);
}

// void	ft_lstremoveif(t_list **lst, const void *ref,
// 			t_ftcmp cmp, t_ftdel del)
// {
// 	t_list	*tmp;

// 	while (*lst != NULL && !cmp((*lst)->content, ref))
// 	{
// 		tmp = *lst;
// 		*lst = (*lst)->next;
// 		ft_lstdelone(tmp, del);
// 	}
// 	if (*lst != NULL)
// 		ft_lstremoveif(&(*lst)->next, ref, cmp, del);
// }

void	ft_lstremoveif(t_list **lst, const void *ref,
			t_ftcmp cmp, t_ftdel del)
{
	t_list	*it;
	t_list	*prev;
	t_list	*node;

	prev = NULL;
	it = *lst;
	while (it != NULL)
	{
		node = it;
		it = it->next;
		if (cmp(it->content, ref))
		{
			prev = node;
			continue ;
		}
		ft_lstdelone(node, del);
		if (prev != NULL)
			prev->next = it;
		else
			*lst = it;
	}
}
