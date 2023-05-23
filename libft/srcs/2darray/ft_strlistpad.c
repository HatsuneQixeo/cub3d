/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlistpad.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:53:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lib2darray.h"

char	**ft_strlistpad(char **strlist, t_ftstrpad ft_strpad, const char c)
{
	char *const		longest = *ft_strlistfind_longest(strlist);
	size_t			len_longest;
	char			**newlist;
	unsigned int	i;

	if (longest == NULL)
		return (ft_strlistdup(strlist));
	newlist = malloc((ft_strcount(strlist) + 1) * sizeof(char *));
	if (newlist == NULL)
		return (NULL);
	len_longest = ft_strlen(longest);
	i = -1;
	while (strlist[++i] != NULL)
	{
		newlist[i] = ft_strpad(strlist[i], len_longest, c);
		if (newlist[i] == NULL)
		{
			ft_strlistclear(newlist);
			return (NULL);
		}
	}
	newlist[i] = NULL;
	return (newlist);
}
