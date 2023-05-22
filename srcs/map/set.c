/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:07 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:07 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cubmap.h"

const char	*set_wall(void)
{
	static const char	arr[] = {Wall, '\0'};

	return (arr);
}

const char	*set_door(void)
{
	static const char	arr[] = {Wall, DoorClose, '\0'};

	return (arr);
}

const char	*set_any(void)
{
	static const char	arr[] = {Wall, DoorClose, DoorOpen, '\0'};

	return (arr);
}
