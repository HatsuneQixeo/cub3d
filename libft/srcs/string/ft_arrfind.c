/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:59:59 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

/**
 * @brief When everybody is writing c in c, I'm writing c++ in c
 * 
 * The use of this function generally require too much setup
 * Would not recommend to use this function more than necessary
 * 
 * On the other hand,
 * 	this function is quite powerful in terms of crosstype comparison
 * Damn, it's like I'm doing polymorphism
 * 
 * @param arr 
 * @param len 
 * @param ft_find 
 * @param ref 
 * @return size_t 
 */
size_t	ft_arrfind(const void *arr, size_t len,
			t_ftfind ft_find, const void *ref)
{
	size_t	i;

	i = 0;
	while (i < len && !ft_find(i, arr, ref))
		i++;
	if (i == len)
		return (-1);
	return (i);
}
