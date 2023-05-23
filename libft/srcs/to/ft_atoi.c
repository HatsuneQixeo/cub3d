/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:31:53 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libto.h"

int	ft_atoi(const char *str, int *ret)
{
	int	nbr;
	int	sign;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	nbr = 0;
	while (ft_isdigit(*str))
	{
		nbr = (nbr * 10) + (*str++ - '0');
		if (nbr * 10 < nbr)
			return (-1);
	}
	*ret = nbr * sign;
	return (0);
}

int	ft_atol(const char *str, long *ret)
{
	long	nbr;
	int		sign;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	nbr = 0;
	while (ft_isdigit(*str))
	{
		nbr = (nbr * 10) + (*str++ - '0');
		if (nbr * 10 < nbr)
			return (-1);
	}
	*ret = nbr * sign;
	return (0);
}

int	ft_atol_range(const char *str, long *ret, const long min, const long max)
{
	long	value;

	if (ft_atol(str, &value) == -1 || !(min <= value && value <= max))
		return (-1);
	*ret = value;
	return (0);
}
