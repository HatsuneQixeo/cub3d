/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_digit_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:16:38 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

int	ft_nbrsize(size_t nbr)
{
	int	digit;

	digit = 1;
	while (nbr / 10)
	{
		nbr /= 10;
		digit++;
	}
	return (digit);
}
