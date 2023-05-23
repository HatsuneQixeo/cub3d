/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 21:30:57 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libto.h"

static char	*itoa_core(unsigned long long nbr, char sign)
{
	char	*str;
	int		digit;

	digit = ft_nbrsize(nbr) + sign;
	str = malloc(digit + 1);
	if (str == NULL)
		return (NULL);
	str[digit] = '\0';
	while (digit--)
	{
		str[digit] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	if (n < 0)
		return (itoa_core((unsigned int)-n, 1));
	else
		return (itoa_core(n, 0));
}

char	*ft_lltoa(long long n)
{
	if (n < 0)
		return (itoa_core((unsigned long long)-n, 1));
	else
		return (itoa_core(n, 0));
}
