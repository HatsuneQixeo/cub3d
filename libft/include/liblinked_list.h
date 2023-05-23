/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liblinked_list.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:52:49 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:52 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBLINKED_LIST_H
# define LIBLINKED_LIST_H

# include "libalgo.h"
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/* Linked list */
t_list		*ft_lstnew(void *content);

void		ft_lstadd_back(t_list **lst, t_list *add);
void		ft_lstadd_front(t_list **lst, t_list *add);

t_list		*ft_lstextract_front(t_list **lst);
t_list		*ft_lstextract_back(t_list **lst);

void		ft_lstdelone(t_list *lst, t_ftdel del);
void		ft_lstclear(t_list **lst, t_ftdel del);

int			ft_lstsize(const t_list *lst);
t_list		*ft_lstselect(const t_list *lst, unsigned int select);
t_list		*ft_lstlast(const t_list *lst);

void		ft_lstiter(t_list *lst, t_ftiter ft);
t_list		*ft_lstmap(const t_list *lst, t_ftmap ft, t_ftdel del);

void		ft_lstremove(t_list **lst, t_list *node, t_ftdel del);
void		ft_lstremoveif(t_list **lst, const void *ref,
				t_ftcmp cmp, t_ftdel del);

t_list		*ft_lstfind(const t_list *lst, const void *ref, t_ftcmp cmp);
t_list		*ft_lstfind_most(const t_list *lst, t_ftcmp cmp);

#endif
