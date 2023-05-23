/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 08:16:49 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:50 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"
#include "libmath.h"

// Error handling
// If the last is in front of first and they are from the same string
// , it will return NULL
// If first and last is pointing to the same string
// , it will be treated as they are individual string
// , for the purpose of ft_strinsert("'", str, "'");
// , ?Note: But i could probably let another function handle that instead?
// , with a name like strenclosed? strsandwich? strquote?
// Return NULL if one of the argument is NULL

/// @brief Function as joining 3 string together
///		Supports inserting a string in between a string
/// @param first The first part of the result string
/// @param insert The string to insert between first and last
/// @param last The part to concatenate after joining first and insert
/// @return NULL is one of the given argument is NULL, malloc failed
///		, or if first and last is reversed in the given pointer.
///		Return the joined string otherwise
/// @note If first and last is pointing to the same string
///		, it will be treated as they are individual string
char	*ft_strinsert(const char *first, const char *insert, const char *last)
{
	char	*str;
	size_t	len;

	if (first == NULL || insert == NULL || last == NULL)
		return (NULL);
	else if (first == last
		|| (first + ft_strlen(first) - ft_strlen(last)) != last)
		return (ft_strmodify(ft_strjoin, ft_strjoin(first, insert), last));
	else if (first > last)
		return (NULL);
	len = ft_strlen(first) + ft_strlen(insert) + 1;
	str = malloc(len);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, first, last - first + 1);
	ft_strlcat(str, insert, len);
	ft_strlcat(str, last, len);
	return (str);
}

/// @brief Cpp's version of strinsert
/// @param src The string to be inserted
/// @param pos The index of where the string will be inserted.
///		If the given index is out of bound, will return a joined string instead
/// @param insert The string to insert
/// @return The inserted string by default.
///		Return NULL if either src or insert is NULL
char	*ft_strinsert_cpp(const char *src, const char *insert, size_t pos)
{
	char	*str;
	size_t	len;
	size_t	len_src;

	if (src == NULL || insert == NULL)
		return (NULL);
	len_src = ft_strlen(src);
	pos = ft_min_sizet(pos, len_src);
	len = len_src + ft_strlen(insert) + 1;
	str = malloc(len);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, src, pos + 1);
	ft_strlcat(str, insert, len);
	ft_strlcat(str, &src[pos], len);
	return (str);
}

char	*ft_strinsert_replace(const char *src, const char *insert,
			size_t pos, size_t len_remove);
