/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort_merge.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 02:27:52 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "liblinked_list.h"

/* Not safe? Can crash if dst is smaller than src */
void	ft_lstcopy(t_list *dst, const t_list *src)
{
	while (src != NULL)
	{
		dst->content = src->content;
		dst = dst->next;
		src = src->next;
	}
}

static void	lstmerge_add(t_list **lst_merged, t_list **lst)
{
	ft_lstadd_back(lst_merged, ft_lstnew((*lst)->content));
	*lst = (*lst)->next;
}

static void	lstmerge(t_list *const begin, t_list *const mid, t_list *const end,
			t_ftcmp cmp)
{
	t_list	*lst_merged;
	t_list	*it_begin;
	t_list	*it_mid;

	lst_merged = NULL;
	it_begin = begin;
	it_mid = mid;
	while (it_begin != mid && it_mid != end)
	{
		if (cmp(it_begin->content, it_mid->content) > 0)
			lstmerge_add(&lst_merged, &it_mid);
		else
			lstmerge_add(&lst_merged, &it_begin);
	}
	while (it_begin != mid)
		lstmerge_add(&lst_merged, &it_begin);
	while (it_mid != end)
		lstmerge_add(&lst_merged, &it_mid);
	ft_lstcopy(begin, lst_merged);
	ft_lstclear(&lst_merged, NULL);
}

size_t	ft_lstrange_node(const t_list *lst, const t_list *node)
{
	size_t	i;

	i = 0;
	if (node == NULL)
		return (ft_lstsize(lst));
	while (lst != NULL && lst != node)
	{
		lst = lst->next;
		i++;
	}
	if (lst == NULL)
		return (-1);
	return (i);
}

void	ft_lstsort_merge(t_list *const begin, t_list *const end, t_ftcmp cmp)
{
	const size_t	len = ft_lstrange_node(begin, end);
	t_list *const	mid = ft_lstselect(begin, len / 2);

	if (len <= 1)
		return ;
	ft_lstsort_merge(begin, mid, cmp);
	ft_lstsort_merge(mid, end, cmp);
	lstmerge(begin, mid, end, cmp);
}
