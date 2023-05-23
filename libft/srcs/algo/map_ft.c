/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:07:50 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

/**
 * @brief A mapping function for making shallow copy (NO-OP)
 * 
 * @param content 
 * @note This function could be used for any data type if I'm not cracked
 * @return void* ) Return the given argument
 */
void	*map_copy(const void *content)
{
	return ((void *)content);
}

/**
 * @brief A mapping function for making deep copy of string
 * 
 * @param content
 * @return void* ) A deep copy of content assuming it's a string
 */
void	*map_strdup(const void *content)
{
	return (ft_strdup(content));
}
