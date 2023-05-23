/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:53:47 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_assert(const int condition, const char *message)
{
	if (condition)
		return ;
	ft_dprintf(STDERR_FILENO, "Assertion failed: %s\n", message);
	exit(EXIT_FAILURE);
}
