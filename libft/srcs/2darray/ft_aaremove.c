/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aaremove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 22:24:00 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "libto.h"

/**
 * Problem with this function is that it doesn't reallocate,
 * means that even if the element is removed, it's still taking up space
 */
void	ft_aaremove(void **aa, t_ftcmp cmp, const void *ref, t_ftdel del)
{
	void	**it;

	it = aa - 1;
	while (*++it != NULL)
	{
		if (cmp(*it, ref))
			*aa++ = *it;
		else if (del)
			del(*it);
	}
	*aa = NULL;
}

/**
 * Under the context of making a shallow copy,
 * this shares the lifetime with the original array
 * 
 * Why?
 * Because I can't just delete the filtered element straight forward
 * outside the scope of this function.
 * Yes, I can just try finding whether the element is in the new element,
 * with a n square time complexity.
 * 
 * Can't really delete the element in here either,
 * that's modifying the original array.
 */
void	**ft_aafilter(void **aa, t_ftcmp cmp, const void *ref, t_ftmap map)
{
	t_list	*lst;
	void	**it;

	lst = NULL;
	it = aa + ft_aasize(aa);
	while (it-- != aa)
	{
		if (cmp(*it, ref))
			ft_lstadd_front(&lst, ft_lstnew(map(*it)));
	}
	return (ft_lsttoaa_clear(&lst));
}
