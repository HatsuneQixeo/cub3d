/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_lsterror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cubmap.h"

void	cubmap_showlsterror(const t_map map, const t_list *lst, const char *msg)
{
	const t_point	*point;
	char			c;

	ft_putendl_fd("Error", 2);
	while (lst != NULL)
	{
		point = lst->content;
		c = map.layout[(int)point->y][(int)point->x];
		if (ft_isprint(c))
			ft_dprintf(2, "	%s: %c", msg, c);
		else
			ft_dprintf(2, "	%s: \\%02x", msg, c);
		point_log(" at ", *point);
		lst = lst->next;
	}
}
