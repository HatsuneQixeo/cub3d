#include "element.h"

static void	*map_invalid_type(const void *ele)
{
	const t_element	*element = ele;

	return (ft_strjoin("Invalid Identifier: ", element->identifier));
}

static void	*map_duplicate_element(const void *ele)
{
	const t_element	*element = ele;

	return (ft_strmerge("Duplicate Elements: %s %s",
			element->identifier, element->properties));
}

int	check_table(const char *idx_table[], const unsigned int length,
			t_element_table element_table)
{
	t_list			*lst_err;
	unsigned int	i;

	lst_err = NULL;
	if (element_table[IdxElemUnknown] != NULL)
		lst_err = ft_lstmap(element_table[IdxElemUnknown],
				map_invalid_type, free);
	i = length;
	while (i--)
	{
		if (element_table[i] == NULL)
			ft_lstadd_front(&lst_err, ft_lstnew(
					ft_strjoin("Missing Element: ", idx_table[i])));
		else if (element_table[i]->next != NULL)
			ft_lstadd_front(&lst_err, ft_lstmap(
					element_table[i], map_duplicate_element, free));
	}
	if (lst_err == NULL)
		return (0);
	ft_putendl_fd("Error", 2);
	ft_lstiter(lst_err, iter_puterrendl);
	ft_lstclear(&lst_err, free);
	return (-1);
}
