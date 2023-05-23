/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstextract_back.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 02:27:52 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:48 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "liblinked_list.h"

t_list	*ft_lstextract_back(t_list **lst)
{
	t_list	*node;
	t_list	*prev;

	node = *lst;
	if (node == NULL)
		return (NULL);
	if (node->next == NULL)
	{
		*lst = NULL;
		return (node);
	}
	prev = NULL;
	while (node->next != NULL)
	{
		prev = node;
		node = node->next;
	}
	prev->next = NULL;
	return (node);
}
