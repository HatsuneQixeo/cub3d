/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:03:02 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

//Note: This funtion set the value byte by byte
//	that means it doesn't function properly if c contain value more than 1 byte
//	despite it asks for an integer value.
void	*ft_memset(void *ptr, int c, size_t bytes)
{
	char	*it;

	it = ptr;
	while (bytes--)
		*it++ = c;
	return (ptr);
}
