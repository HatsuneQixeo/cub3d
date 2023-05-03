#ifndef ELEMENT_H
# define ELEMENT_H

typedef struct s_element
{
	char	*identifier;
	char	*properties;
}			t_element;

enum e_table_index
{
	IdxIdentifierNorth,
	IdxIdentifierEast,
	IdxIdentifierSouth,
	IdxIdentifierWest,
	IdxIdentifierFloor,
	IdxIdentifierCeiling,
	IdxIdentifierUnknown,
	IdxIdentifierAmount
};

t_element	*element_new(char *identifier, char *properties);
void		element_del(void *content);

#endif
