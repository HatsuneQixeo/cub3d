/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:08:16 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:52 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# include "ansi.h"
# include "libis.h"
# include "libstring.h"
# include "get_next_line.h"
# include "libalgo.h"
# include "libto.h"
# include "ft_printf.h"
# include "liblinked_list.h"
# include "lib2darray.h"
# include <assert.h>

# ifndef SAN
#  define SAN	0
# endif

/* Io with certain side effect */
char	*ft_prompt(const char *prompt);
void	ft_assert(int condition, const char *message);

#endif
