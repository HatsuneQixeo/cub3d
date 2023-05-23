/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libstring.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:52:49 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:52 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBSTRING_H
# define LIBSTRING_H

# include <stdlib.h>
# include "libis.h"
# include "libalgo.h"

# define SPACES	" \t"

typedef char	*(*t_modifier)(const char *str1, const char *str2);

size_t	ft_arrfind(const void *arr, size_t len,
			t_ftfind ft_find, const void *ref);

/* Padding */
typedef char	*(*t_ftstrpad)(const char *str, size_t len, char c);
char	*ft_strpad_right(const char *str, const size_t len, const char c);
char	*ft_strpad_left(const char *str, const size_t len, const char c);

/* Mem */
void	ft_bzero(void *str, size_t len);
void	*ft_calloc(size_t len, size_t size);
void	*ft_memchr(const void *str, int c, size_t bytes);
int		ft_memcmp(const void *str1, const void *str2, size_t bytes);
void	*ft_memcpy(void *dst, const void *src, size_t bytes);
void	*ft_memmove(void *dst, const void *src, size_t bytes);
void	*ft_memset(void *str, int c, size_t bytes);
void	ft_swapbyte(void *a, void *b);
void	ft_memswap(void *ptr1, void *ptr2, size_t bytes);
char	*ft_memprintable(const void *src, const char *base, size_t bytes);

/* String */
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t size);

char	*ft_strchr(const char *str, int c);
char	*ft_strchr_is(const char *str, t_ftis ft_is);
char	*ft_strrchr(const char *str, int c);

size_t	ft_strcount_chris(const char *str, t_ftis ft_is);
size_t	ft_strcount_chrset(const char *str, const char *set);

int		ft_strcmp(const char *str1, const char *str2);
int		ft_strncmp(const char *str1, const char *str2, size_t n);

char	*ft_strstr(const char *str, const char *to_find);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);

char	*ft_strskip_chr(const char *str, char c);
char	*ft_strskip_is(const char *str, t_ftis ft_is);
char	*ft_strskip_set(const char *str, const char *set);

char	*ft_strdup(const char *str1);
char	*ft_strcreate(char set, size_t len);
char	*ft_substr(const char *str, unsigned int home, size_t len);
char	*ft_strtrim(const char *src, const char *set);
char	*ft_strinsert(const char *first, const char *insert, const char *last);
char	*ft_strmodify(t_modifier ft_str, char *src, const char *mod);
char	*ft_strcombine(char *str1, char *str2);
char	*ft_strmerge(const char *str_format, ...);

char	*ft_strjoin(const char *str1, const char *str2);
char	*ft_strrjoin(const char *str, const char *add);

void	ft_striteri(char *str, t_ftiteri ft_iteri);
char	*ft_strmapi(const char *str, char (*ft)(unsigned int, char));

char	*ft_strprintable(const char *src, const char *base);
char	*ft_strprintable_sign(const char *src);

char	**ft_split(const char *str, char c);
char	**ft_split_is(const char *str, t_ftis ft_is);

char	*strmod_clear(const char *str_clear, const char *str_void);
char	*strmod_realloc(const char *src, const char *str_void);
char	*strmod_strstrdup(const char *src, const char *find);
char	*strmod_substr(const char *src, const char *src_end);
char	*strmod_replace(const char *replaced, const char *by);

/* Callback Functions */
char	mapi_capitalize(unsigned int i, char c);
char	mapi_lower(unsigned int i, char c);
char	mapi_miku(unsigned int i, char c);
char	mapi_upper(unsigned int i, char c);

void	iteri_tolower(unsigned int i, void *str);
void	iteri_toupper(unsigned int i, void *str);

#endif
