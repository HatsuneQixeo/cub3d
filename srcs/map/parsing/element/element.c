/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:06 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:06 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "element.h"
#include "libft.h"

t_element	*element_new(char *identifier, char *properties)
{
	t_element	*element;

	element = malloc(sizeof(t_element));
	if (element == NULL)
		return (NULL);
	element->identifier = identifier;
	element->properties = properties;
	return (element);
}

void	element_del(void *content)
{
	t_element	*element;

	element = content;
	free(element->identifier);
	free(element->properties);
	free(content);
}

void	element_show(void *content)
{
	const t_element	*element = content;

	ft_dprintf(2, "%s: %s\n", element->identifier, element->properties);
}
