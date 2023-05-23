/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libto.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:52:49 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:52 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBTO_H
# define LIBTO_H

# include "libis.h"
# include "libmath.h"
# include "libstring.h"
# include "libalgo.h"
# include "liblinked_list.h"
# include "lib2darray.h"

/* To */
t_list	*ft_aatolst(void **aa, t_ftmap ft_map, t_ftdel del);
t_list	*ft_aatolst_clear(void **aa);

int		ft_atoi(const char *str, int *ret);
int		ft_atol(const char *str, long *ret);
int		ft_atol_range(const char *str, long *ret, long min, long max);

char	*ft_itoa(int n);
char	*ft_lltoa(long long n);

char	*ft_lsttostr(t_list *lst);
char	*ft_lsttostr_clear(t_list **lst);
char	*ft_lsttostr_delimiter(t_list *lst, const char *delimiter);
char	*ft_lsttostr_delimiter_clear(t_list **lst, const char *delimiter);

void	**ft_lsttoaa(const t_list *lst, t_ftmap ft_map, t_ftdel del);
void	**ft_lsttoaa_clear(t_list **lst);

int		ft_tolower(int c);
int		ft_toupper(int c);

char	*ft_utoa_base(size_t n, const char *base);
int		ft_validbase(const char *base);

#endif
