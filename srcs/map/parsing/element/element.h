#ifndef ELEMENT_H
# define ELEMENT_H

typedef struct s_element
{
	char	*identifier;
	char	*properties;
}			t_element;

enum e_table_index
{
	IdxElemNorth,
	IdxElemEast,
	IdxElemSouth,
	IdxElemWest,
	IdxElemFloor,
	IdxElemCeiling,
	IdxElemUnknown,
	IdxElemAmount
};

t_element	*element_new(char *identifier, char *properties);
void		element_del(void *content);
void		element_show(void *content);

#endif
