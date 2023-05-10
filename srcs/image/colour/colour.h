/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:47 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOUR_H
# define COLOUR_H

# include <stdint.h>

typedef uint8_t		t_colour_byte;
typedef uint32_t	t_colour;

enum e_colour_value
{
	ValueR = 0x00010000,
	ValueG = 0x00000100,
	ValueB = 0x00000001,
	ValueA = 0x01000000,
	ValueRGB = ValueR | ValueG | ValueB,
	ValueAll = ValueRGB | ValueA,
};

t_colour_byte	colour_getmask(t_colour colour, enum e_colour_value value);
void			colour_setmask(t_colour *colour, t_colour_byte set,
					enum e_colour_value value);
t_colour		colour_from_rgba(t_colour_byte red, t_colour_byte green,
					t_colour_byte blue, t_colour_byte alpha);
t_colour		colour_from_percentage(double red, double green,
					double blue, double alpha);
t_colour		colour_invert(t_colour colour, enum e_colour_value value);
t_colour		colour_add(t_colour a, t_colour b);

void			ft_intset(int *arr, unsigned int size, int value);

#endif
