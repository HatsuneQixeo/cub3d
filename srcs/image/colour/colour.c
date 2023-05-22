/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 22:58:08 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/23 03:46:05 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "colour.h"
#include "libft.h"

/**
 * No, I don't really recommend this approach,
 * it's too inconvenient to access the individual byte value.
 * 
 * This approach is much more convenient for getting the individual byte value:
 * union u_colour
 * {
 * 	uint32_t	value;
 * 	struct
 * 	{
 * 		uint8_t	blue;
 * 		uint8_t	green;
 * 		uint8_t	red;
 * 		uint8_t	alpha;
 * 	}			comp;
 * };
 * 
 * But I didn't actually use any of the byte manipulation functions anyway,
 * outside of a failed attempt at implementing colour addition function.
 */

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
 * 
 * @note Have not yet tested what would happen if multiple values were given
 * In theory the biggest byte should be prioritize
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
 * @note This can set multiple values to the given value
 */
void	colour_setmask(t_colour *colour, const t_colour_byte set,
			const enum e_colour_value value)
{
	*colour = (*colour & ~(value * 0xff)) | (set * value);
}

/**
 * Chose this approach over getmask and setmask to support multiple masks,
 * which is not possible with getmask,
 * and setmask can only set a given value for all the given mask
 */
t_colour	colour_invert(const t_colour colour,
			const enum e_colour_value value)
{
	const t_colour	mask = value * 0xff;

	return ((colour & ~mask) | (~colour & mask));
}
