/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib2darray.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:52:49 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:52 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIB2DARRAY_H
# define LIB2DARRAY_H

# include "libalgo.h"
# include "libstring.h"

/**
 * Facing a lot of questions with NULL return value from a map function,
 * and the fact that 2darray is terminated by NULL.
 * 
 * - If it is terminated by NULL, how should it react to ft_map returning NULL?
 * 		1) If we just assumed it is meant to be excluded,
 * 		this could easily result in undefined behaviour
 * 		if the memory is temporarily unavailable.
 * 		2) If we cleared everything under the assumption of malloc error,
 * 		then linked list with a NULL content
 * 		would cause a lot of potential problem.
 * 
 * - If NULL could not be assumed as the end of the array,
 * 	wouldn't it be too easy to crash the program ?
 * Not to mention the inconvenience that every related functions
 * would need to ask for the length.
 * 
 * Let's make a assumption that map function returning NULL is an error,
 * that makes things slightly easier.
 */

/* Size */
int		ft_aasize(void **aa);
int		ft_strcount(char **strlist);

/* Clear */
void	ft_aaclear(void **aa, t_ftdel del);
void	ft_strlistclear(char **strlist);

/* Search */
void	**ft_aafind(void **aa, const void *ref, t_ftcmp cmp);
char	**ft_strlistfind_prefix(char **strlist, const char *prefix);

/* Min/Max Element */
void	**ft_aafind_min(void **aa, t_ftcmp cmp);
void	**ft_aafind_max(void **aa, t_ftcmp cmp);
char	**ft_strlistfind_longest(char **strlist);

/* Iteri */
void	ft_aaiteri(void *aa, t_ftiteri ft_iteri);
void	ft_strlistmod(char **strlist, const char *mod, t_modifier ft_str);

/* Map */
void	**ft_aamap(void **src, t_ftmap ft_map, t_ftdel del);
void	**ft_aarenew(void **src);
char	**ft_strlistdup(char **strlist);

/* Remove */
void	ft_aaremove(void **aa, t_ftcmp cmp, const void *ref, t_ftdel del);

/* Other */
char	**ft_strlistpad(char **strlist, t_ftstrpad ft_strpad, char c);

char	**ft_strlistcombine(char **srclist1, char **srclist2);

#endif
