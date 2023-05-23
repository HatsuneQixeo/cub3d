/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:53:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "liblinked_list.h"

void	del_shallowlist(void *list)
{
	t_list	*lst;

	lst = list;
	ft_lstclear(&lst, NULL);
}
