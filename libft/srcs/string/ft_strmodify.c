/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmodify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 01:34:01 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

/**
 * @brief Execute the given function with given arguments and free src after
 * 
 * @param ft_str The operation for provided strings
 * @param src The first string to pass into the given function and free after
 * @param mod The second string to pass into the given function
 * @return char* The return value of the given function
 * @bug There is no known bug, but this function leaves a dangling pointer.
 * It's left there as it is for the flexibility of taking in a return value
 * @namespace strmod
 * @note Common use functions:
 * ft_strjoin, ft_strrjoin, ft_strtrim
 * 
 * @note Note for given function:
 * Implement ft_strdup for unexpected argument to retain given string,
 * instead of returning NULL in given function
 */
char	*ft_strmodify(t_modifier ft_str, char *src, const char *mod)
{
	char	*str;

	str = ft_str(src, mod);
	free(src);
	return (str);
}
