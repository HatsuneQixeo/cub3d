/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:41:10 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>
#include <assert.h>

static char	*read_line(int fd, char *str_saved)
{
	char	str_part[BUFFER_SIZE + 1];
	size_t	len_read;

	len_read = BUFFER_SIZE;
	while (!ft_strchr(str_saved, '\n') && len_read == BUFFER_SIZE)
	{
		len_read = read(fd, str_part, BUFFER_SIZE);
		if (len_read == SIZE_MAX)
		{
			perror("get_next_line: ");
			break ;
		}
		str_part[len_read] = '\0';
		str_saved = ft_strmodify(ft_strjoin, str_saved, str_part);
	}
	return (str_saved);
}

static char	*separator(char **p_str_saved)
{
	const char	*str_nl = ft_strchr(*p_str_saved, '\n');
	char		*str_main;
	char		*str_tmp;

	if (str_nl != NULL)
	{
		str_main = ft_substr(*p_str_saved, 0, ++str_nl - *p_str_saved);
		str_tmp = ft_strdup(str_nl);
		free(*p_str_saved);
	}
	else if (**p_str_saved != '\0')
	{
		str_main = *p_str_saved;
		str_tmp = NULL;
	}
	else
	{
		str_main = NULL;
		str_tmp = NULL;
		free(*p_str_saved);
	}
	*p_str_saved = str_tmp;
	return (str_main);
}

char	*get_next_line(int fd)
{
	static char	*str_saved[1024];

	static_assert(BUFFER_SIZE >= 1, "Invalid Buffer Size");
	if ((unsigned int)fd >= 1024)
		return (NULL);
	if (str_saved[fd] == NULL)
		str_saved[fd] = ft_strdup("");
	str_saved[fd] = read_line(fd, str_saved[fd]);
	return (separator(&str_saved[fd]));
}
