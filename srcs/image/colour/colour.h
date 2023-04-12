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
	ValueA = 0x01000000
};

t_colour_byte	colour_getmask(const t_colour colour,
					const enum e_colour_value value);
void			colour_setmask(t_colour *colour, const t_colour_byte set,
					const enum e_colour_value value);
t_colour		colour_from_rgba(const t_colour_byte red,
					const t_colour_byte green,
					const t_colour_byte blue,
					const t_colour_byte alpha);
t_colour		colour_from_percentage(const double red, const double green,
					const double blue, const double alpha);
void			ft_intset(int *arr, const unsigned int size, const int value);

#endif
