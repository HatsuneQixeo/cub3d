/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colour.h"
#include "libft.h"

/**
 * @brief 
 * (value * 0xff)
 * turns the value into mask
 * 
 * & (bitwise and)
 * filters out the value inside the given byte
 * 
 * /
 * shifts the value so that it fits into a byte
 */
t_colour_byte	colour_getmask(const t_colour colour,
				const enum e_colour_value value)
{
	return ((colour & (value * 0xff)) / value);
}

/**
 * @brief 
 * 
 * (value * 0xff)
 * turns the value into mask
 * 
 * & (bitwise and)
 * in combination with
 * ~ (bitwise not)
 * preserve the value in other mask, filter out the value in given mask
 * 
 * (set * value)
 * shifts the byte into the belonging mask
 * 
 * |
 * adds the value into the mask
 * 
 */
void	colour_setmask(t_colour *colour, const t_colour_byte set,
			const enum e_colour_value value)
{
	*colour = (*colour & ~(value * 0xff)) | (set * value);
}

t_colour	colour_from_rgba(const t_colour_byte red,
				const t_colour_byte green,
				const t_colour_byte blue,
				const t_colour_byte alpha)
{
	return ((red * ValueR)
		+ (green * ValueG)
		+ (blue * ValueB)
		+ (alpha * ValueA));
}

t_colour	colour_from_percentage(const double red, const double green,
				const double blue, const double alpha)
{
	ft_assert(0 <= red && red <= 1, "red is not between 0 and 1");
	ft_assert(0 <= green && green <= 1, "green is not between 0 and 1");
	ft_assert(0 <= blue && blue <= 1, "blue is not between 0 and 1");
	ft_assert(0 <= alpha && alpha <= 1, "alpha is not between 0 and 1");
	return (colour_from_rgba(
			red * 0xff,
			green * 0xff,
			blue * 0xff,
			alpha * 0xff));
}

void	ft_intset(int *arr, const unsigned int size, const int value)
{
	unsigned int	i;

	i = 0;
	while (i < size)
		arr[i++] = value;
}
