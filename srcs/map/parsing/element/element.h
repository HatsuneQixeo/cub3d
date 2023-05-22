/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 03:46:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:08 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ELEMENT_H
# define ELEMENT_H

# include "libft.h"

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
	idx_elem_amount
};

typedef t_list	*t_element_table[idx_elem_amount];

t_element	*element_new(char *identifier, char *properties);
void		element_del(void *content);
void		element_show(void *content);

#endif
