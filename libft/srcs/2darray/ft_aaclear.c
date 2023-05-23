/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aaclear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 21:40:42 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lib2darray.h"

void	ft_aaclear(void **aa, t_ftdel del)
{
	unsigned int	y;

	if (aa == NULL)
		return ;
	else if (del != NULL)
	{
		y = -1;
		while (aa[++y] != NULL)
			del(aa[y]);
	}
	free(aa);
}

void	ft_strlistclear(char **strlist)
{
	ft_aaclear((void **)strlist, free);
}
