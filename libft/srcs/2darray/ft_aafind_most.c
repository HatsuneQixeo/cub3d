/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aafind_most.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:53:46 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:46 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lib2darray.h"

static int	islesser(t_ftcmp cmp, void *ref1, void *ref2)
{
	return (cmp(ref1, ref2) < 0);
}

static int	isgreater(t_ftcmp cmp, void *ref1, void *ref2)
{
	return (cmp(ref1, ref2) > 0);
}

typedef int	(*t_ftcmpis)(t_ftcmp cmp, void *ref1, void *ref2);

static void	**aafind_most(void **aa, t_ftcmp cmp, t_ftcmpis cmpis)
{
	void			**most;
	unsigned int	i;

	if (aa[0] == NULL)
		return (aa);
	most = aa;
	i = 0;
	while (aa[++i] != NULL)
	{
		if (cmpis(cmp, aa[i], *most))
			most = &aa[i];
	}
	return (most);
}

void	**ft_aafind_max(void **aa, t_ftcmp cmp)
{
	return (aafind_most(aa, cmp, isgreater));
}

void	**ft_aafind_min(void **aa, t_ftcmp cmp)
{
	return (aafind_most(aa, cmp, islesser));
}
