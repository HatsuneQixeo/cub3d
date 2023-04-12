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

#include "image.h"

int	putoffset_default(const int pos, const int size)
{
	return (pos);
}

int	putoffset_centered(const int pos, const int size)
{
	return (pos - size / 2);
}

int	putoffset_inverted(const int pos, const int size)
{
	return (pos - size);
}
