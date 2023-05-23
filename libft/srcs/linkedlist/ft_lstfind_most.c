/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind_most.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 02:27:52 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:48 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "liblinked_list.h"

t_list	*ft_lstfind_most(const t_list *lst, t_ftcmp cmp)
{
	const t_list	*most = lst;
	const t_list	*node;

	if (lst == NULL)
		return (NULL);
	node = most->next;
	while (node != NULL)
	{
		if (cmp(most->content, node->content) < 0)
			most = node;
		node = node->next;
	}
	return ((t_list *)most);
}
