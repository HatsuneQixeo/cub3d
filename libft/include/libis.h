/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libis.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:52:49 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:52 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBIS_H
# define LIBIS_H

# include <stdint.h>
# include <limits.h>
# include <stdlib.h>

typedef int	(*t_ftis)(int c);
/* Is */
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_islower(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isupper(int c);

int		stris_only(const char *str, t_ftis ft_is);
typedef int	(*t_ftstris)(const char *str);
int		stris_empty(const char *str);
int		stris_numeric(const char *str);

typedef int	(*t_ftcmp)(const void *ref1, const void *ref2);
int		cmp_str(const void *str1, const void *str2);
int		cmp_strreverse(const void *str1, const void *str2);
int		cmp_strprefix(const void *str, const void *prefix);
int		cmp_strsuffix(const void *str, const void *suffix);
int		cmp_strlen(const void *str1, const void *str2);

int		ft_memisempty(const void *ptr, size_t bytes);

#endif
