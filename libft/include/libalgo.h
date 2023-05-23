/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libalgo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:52:49 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:52 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBALGO_H
# define LIBALGO_H

# include "libis.h"
# include <stdlib.h>

# define ITNAME_DEFAULT	"it"
# define NOTFOUND		SIZE_MAX

typedef const char		*(*t_ftsetname)(const char *name);
const char	*iteri_name(const char *newname);

/* Del */
typedef void			(*t_ftdel)(void *content);
void		del_shallowlist(void *list);

/* Iteri */
typedef void			(*t_ftiteri)(unsigned int i, void *aa);
void		iteri_putendl(unsigned int i, void *strlist);
void		iteri_showstr(unsigned int i, void *strlist);
void		iteri_showaddress(unsigned int i, void *aa);
void		iteri_lstclear_shallow(unsigned int i, void *arr_lst);

/* Map */
typedef void			*(*t_ftmap)(const void *content);
void		*map_copy(const void *content);
void		*map_strdup(const void *content);

typedef int				(*t_ftfind)(unsigned int i, const void *arr,
			const void *ref);

typedef struct s_list	t_list;
typedef void			(*t_ftiter)(void *content);
/* Linked list*/
const char	*iter_name(const char *newname);
void		iter_showstr(void *str);
void		iter_puterrendl(void *str);

/* Sorting */
void		sort_insertion(void *begin, size_t len, size_t data_size,
				t_ftcmp cmp);
void		ft_lstsort_merge(t_list *begin, t_list *end, t_ftcmp cmp);

#endif
