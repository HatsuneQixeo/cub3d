/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_offset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:24:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/04/12 23:24:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	putoffset_default(const double size)
{
	return (0);
	(void)size;
}

double	putoffset_centered(const double size)
{
	return (-(size / 2));
}

double	putoffset_inverted(const double size)
{
	return (-size);
}
