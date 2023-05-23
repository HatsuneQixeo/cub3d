/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 00:38:28 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	**ft_readfile(const char *path)
{
	const int	fd = open(path, O_RDONLY);
	t_list		*lst;
	char		*str_part;

	if (fd == -1)
		return (NULL);
	lst = NULL;
	while (1)
	{
		str_part = get_next_line(fd);
		if (str_part == NULL)
			break ;
		str_part = ft_strmodify(ft_strtrim, str_part, "\n");
		ft_lstadd_back(&lst, ft_lstnew(str_part));
	}
	close(fd);
	return ((char **)ft_lsttoaa_clear(&lst));
}
