/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpad.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:53:51 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libstring.h"

static char	*strpad_join(t_modifier ft_join, const char *str,
			const size_t pad_len, const char c)
{
	const size_t	len = ft_strlen(str);

	if (len < pad_len)
		return (ft_strmodify(ft_join, ft_strcreate(c, pad_len - len), str));
	else
		return (ft_strdup(str));
}

char	*ft_strpad_right(const char *str, const size_t len, const char c)
{
	return (strpad_join(ft_strrjoin, str, len, c));
}

char	*ft_strpad_left(const char *str, const size_t len, const char c)
{
	return (strpad_join(ft_strjoin, str, len, c));
}
