#include "element.h"
#include "ft_printf.h"

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
