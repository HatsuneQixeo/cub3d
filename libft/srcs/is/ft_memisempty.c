/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memisempty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:53:48 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:48 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

/* Maybe someday? */
int	ft_memisempty(const void *ptr, const size_t bytes)
{
	const char	*it = ptr;
	const char	*end = it + bytes;

	while (it != end && *it == 0x00)
		it++;
	return (it == end);
}
