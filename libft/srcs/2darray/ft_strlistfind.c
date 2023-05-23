/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlistfind.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:53:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lib2darray.h"

char	**ft_strlistfind_longest(char **strlist)
{
	return ((char **)ft_aafind_max((void **)strlist, cmp_strlen));
}
