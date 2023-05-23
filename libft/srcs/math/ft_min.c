/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 08:50:24 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:49 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <math.h>

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

long	ft_min_long(long a, long b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

size_t	ft_min_sizet(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double	ft_dmin(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double	ft_dmin_abs(double a, double b)
{
	if (fabs(a) < fabs(b))
		return (a);
	else
		return (b);
}
