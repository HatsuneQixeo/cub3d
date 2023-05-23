/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlistmod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:16:55 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

void	ft_strlistmod(char **strlist, const char *mod, t_modifier ft_mod)
{
	char	**it;

	if (strlist == NULL || ft_mod == NULL)
		return ;
	it = strlist;
	while (*strlist != NULL)
	{
		*it = ft_strmodify(ft_mod, *strlist++, mod);
		it += *it != NULL;
	}
	*it = NULL;
}

/**
 * @brief Remove the string if it matches, Dedicated for strlistmod
 * 
 * @param str 
 * @param str_rm 
 * @return char* NULL if the string matches
 * otherwise it will return the a copy of the data
 */
/* This is just aaremove */
char	*strmod_rmstr(const char *str, const char *str_rm)
{
	if (ft_strcmp(str, str_rm))
		return (ft_strdup(str));
	else
		return (NULL);
}

/// @test Not 'str'string''string'ing'
/// @brief Remove substring in a string, dedicated for strmodify
/// @param str The string to remove the substring
/// @param str_rm The substring to be removed
/// @return The string which does not contain any substr of str_rm
// char	*strmod_rmsubstr(const char *str, const char *str_rm)
// {
// 	char	*substr;
// 	char	*str_new;
// 	size_t	len_rm;

// 	str_new = ft_strdup(str);
// 	if (str_new == NULL)
// 		return (NULL);
// 	substr = ft_strstr(str_new, str_rm);
// 	if (substr == NULL)
// 		return (str_new);
// 	len_rm = ft_strlen(str_rm);
// 	while (substr != NULL)
// 	{
// 		ft_memmove(substr, substr + len_rm, ft_strlen(substr + len_rm) + 1);
// 		substr = ft_strstr(substr, str_rm);
// 	}
// 	return (ft_strmodify(strmod_realloc, str_new, NULL));
// }

// void	strformat_rmsubstr(char *str, const char *str_rm)
// {
// 	const char		*find;
// 	const size_t	len_rm = ft_strlen(str_rm);

// 	while (1)
// 	{
// 		find = ft_strstr(str, str_rm);
// 		if (find == NULL)
// 			break ;
// 		ft_memmove(find, find + len_rm, ft_strlen(find + len_rm) + 1);
// 	}
// }
