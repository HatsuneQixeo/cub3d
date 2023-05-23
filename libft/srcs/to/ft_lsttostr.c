/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttostr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 10:04:01 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:51 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libto.h"

size_t	ft_lsttotal_strlen(t_list *lst)
{
	size_t	total;

	total = 0;
	while (lst != NULL)
	{
		if (lst->content != NULL)
			total += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (total);
}

char	*ft_lsttostr(t_list *lst)
{
	char			*str;
	const size_t	len = ft_lsttotal_strlen(lst) + 1;

	str = malloc(len);
	if (str == NULL)
		return (NULL);
	str[0] = '\0';
	while (lst != NULL)
	{
		if (lst->content != NULL)
			ft_strlcat(str, lst->content, len);
		lst = lst->next;
	}
	return (str);
}

char	*ft_lsttostr_delimiter(t_list *lst, const char *delimiter)
{
	char			*str;
	const size_t	size = ft_lsttotal_strlen(lst)
		+ (ft_strlen(delimiter) * (ft_lstsize(lst) - 1)) + 1;

	if (lst == NULL)
		return (ft_strdup(""));
	str = malloc(size);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, lst->content, size);
	lst = lst->next;
	while (lst != NULL)
	{
		ft_strlcat(str, delimiter, size);
		if (lst->content != NULL)
			ft_strlcat(str, lst->content, size);
		lst = lst->next;
	}
	return (str);
}

char	*ft_lsttostr_delimiter_clear(t_list **lst, const char *delimiter)
{
	char	*str;

	str = ft_lsttostr_delimiter(*lst, delimiter);
	ft_lstclear(lst, free);
	return (str);
}

char	*ft_lsttostr_clear(t_list **lst)
{
	char	*str;

	str = ft_lsttostr(*lst);
	ft_lstclear(lst, free);
	return (str);
}
