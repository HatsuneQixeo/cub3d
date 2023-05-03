#include "element.h"
#include <stdlib.h>

t_element	*element_new(char *identifier, char *properties)
{
	t_element	*element;

	element = malloc(sizeof(t_element));
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
}
