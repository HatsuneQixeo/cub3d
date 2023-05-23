/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmod_ft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:54:44 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/**
** Although wide usage of it is somewhat discouraged
** due to extra context needed and improper function template,
** but it can be serves as a backup plan against norminette.
** ex:
	if (condition)
	{
		free(str);
		return (NULL);
	}
**	->
	if (condition)
		return (ft_strmodify(strmod_clear, str, NULL));
*/
char	*strmod_clear(const char *str_clear, const char *str_void)
{
	return (NULL);
	(void)str_clear;
	(void)str_void;
}

char	*strmod_transfrom(const char *from, const char *to)
{
	return (ft_strdup(to));
	(void)from;
}

/**
 * char	*tmp;
 * 
 * tmp = newstr(str);
 * free(str);
 * str = tmp;
 * 
 * ->
 * 
 * str = ft_strmodify(strmod_replace, str, newstr(str));
 * 
 * 
 * 
 */
char	*strmod_replace(const char *replaced, const char *by)
{
	return ((char *)by);
	(void)replaced;
}

/**
** Primarily used for saving memory after shrinking the string
** Function that could be used to shrink a string for example are memmove
*/
char	*strmod_realloc(const char *src, const char *str_void)
{
	return (ft_strdup(src));
	(void)str_void;
}

// Skip the starting part
// ALT: ft_memmove
// Note: experimental function, current usage is unclear
// Find the string and duplicate it
// , dedicated for strmodify
// , but could be use individually as the way it is stated
// char	*strmod_strstrdup(const char *src, const char *find)
// {
// 	const char	*substr = ft_strstr(src, find);

// 	if (substr == NULL)
// 		return (NULL);
// 	return (ft_strdup(substr));
// }

// Limit the end part
// BIGNOTE: This is an experimental function
// Future Note: Making a substrfree is probably the most universal solution
// , OR just null terminating the rest of the string duh

// errhandling1
// 	else if (src_end > ft_strchr(src, '\0'))
// Passing in another string is undefined
// , but it can handle potential inaccurate value
// Note: Could be left out for substr to handle

// errhandling2 (Active)
// 	else if (!ft_strstr(src, src_end))
// Does it's job well, but passing inaccurate value will trigger it
// Note: They do not co-exist

// Note: Passing the same address will result in the src being emptied
// , could be redifined to return the original string instead
// , (off the original intention)
// char	*strmod_substr(const char *src, const char *src_end)
// {
// 	if (src == NULL)
// 		return (NULL);
// 	else if (src_end == NULL || src_end < src || !ft_strstr(src, src_end))
// 		return (ft_strdup(src));
// 	return (ft_substr(src, 0, src_end - src));
// }

// Alternative that doesn't require external function
// {
// 	void	strformat_strstr(char *src, const char *find)
// 	{
// 		if (src && find)
// 			ft_memmove(src, ft_strstr(src, find), ft_strlen(find) + 1);
// 	}

// 	void	strformat_substr(char *src, const char *src_end)
// 	{
// 		if (!src)
// 			return ;
// 		else if (!src_end || src_end < src || !ft_strstr(src, src_end))
// 			return ;
// 		ft_bzero(src_end, ft_strlen(src_end));
// 	}
// }

/**
 * @brief I have no idea this was even possible in the first place
 * 		Yes, I tested it, no compile error at all
 * @param str1 
 * @param str2 
 * @return char* 
 */
// char	*strmod_free(const char *str1, const char *str2)
// {
// 	free((void *)str1);
// 	free((void *)str2);
// 	return (NULL);
// }
