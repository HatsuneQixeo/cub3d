#include <stdio.h>
#include <string.h>
#include "libft.h"

char	*ft_strprintable_sign(const char *src);
typedef int (*t_ftput)(const char *, int);

/* Envp
	It is a 2d array allocated on stack
	meaning modification is allowed toward every character and pointer
	but not free for obvious reason
*/
// int	main(int argc, char **argv, char **envp)
// {
// 	ft_strlistiteri(envp, iteristr_showstr);
// 	*(envp + 1) = NULL;
// 	ft_strlistiteri(envp, iteristr_showstr);
// 	free(*envp);
// }

/*
	Only calling strlcat once per loop
	but need extra space for storing joined delimiter and src
*/
char	*ft_strmultiply(const char *src, const char *delimiter, unsigned int amount)
{
	char			*str;
	char			*str_joined;
	const size_t	src_len = ft_strlen(src);
	const size_t	total_len = src_len * amount
				+ (ft_strlen(delimiter) * (amount - 1));

	if (amount == 0 || total_len == 0)
		return (ft_strdup(""));
	else if (amount == 1)
		return (ft_strdup(src));
	str_joined = ft_strjoin(delimiter, src);
	if (str_joined == NULL)
		return (NULL);
	str = malloc(total_len + 1);
	if (str == NULL)
	{
		free(str_joined);
		return (NULL);
	}
	ft_strlcpy(str, src, src_len + 1);
	while (--amount)
		ft_strlcat(str, str_joined, total_len + 1);
	free(str_joined);
	return (str);
}

/* No memory allocation for anything else but calling strlcat twice */
// char	*ft_strmultiply(const char *src, const char *delimiter, unsigned int amount)
// {
// 	char			*str;
// 	const size_t	src_len = ft_strlen(src);
// 	const size_t	total_len = src_len * amount
// 				+ (ft_strlen(delimiter) * (amount - 1));

// 	if (amount == 0 || total_len == 0)
// 		return (ft_strdup(""));
// 	str = malloc(total_len + 1);
// 	if (str == NULL)
// 		return (NULL);
// 	ft_strlcpy(str, src, src_len + 1);
// 	while (--amount)
// 	{
// 		ft_strlcat(str, delimiter, total_len + 1);
// 		ft_strlcat(str, src, total_len + 1);
// 	}
// 	return (str);
// }

// int	main(void)
// {
// 	t_list	*lst;
// 	char	**aa;

// 	lst = NULL;
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("Miku")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("is")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("cute")));
// 	aa = (char **)ft_lsttoaa_clear(&lst);
// 	ft_strlistiteri(aa, iteristr_showstr);
// 	system("leaks -q test.miku");
// }

int	ft_strcmp_void(const void *s1, const void *s2)
{
	return (ft_strcmp(s1, s2));
}

unsigned int	ft_aacountif(void **arr, unsigned int len, t_ftcmp cmp, const void *ref)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (cmp(arr[i], ref) == 0)
			count++;
		i++;
	}
	return (count);
}

void	test_remove(void **strlist, const char *ref, t_ftdel del)
{
	char **const		strlist_copy = (char **)ft_aamap(strlist, map_copy);
	const unsigned int	length_before = ft_aasize(strlist);
	const unsigned int	to_remove = ft_aacountif(strlist, ft_aasize(strlist), ft_strcmp_void, ref);
	
	ft_aaremove(strlist, ft_strcmp_void, ref, del);
	const unsigned int	leftover = ft_aacountif(strlist, ft_aasize(strlist), ft_strcmp_void, ref);
	const unsigned int	length_after = ft_aasize(strlist);

	if (leftover != 0)
		printf("Error: %u leftover after remove\n", leftover);
	else if (length_after > length_before - to_remove)
		printf("Error: Did not removed every reference to remove\n");
	else if (length_after < length_before - to_remove)
		printf("Error: Removed unrelated element\n");
	else
	{
		free(strlist);
		free(strlist_copy);
		return ;
	}
	iteri_name("Before remove");
	ft_strlistiteri(strlist_copy, iteri_showstr);
	ft_printf("\n");
	iteri_name("After remove");
	ft_strlistiteri((char **)strlist, iteri_showstr);
	ft_printf("\n");
	free(strlist);
	free(strlist_copy);
}

// int	main(void)
// {
// 	t_list	*lst;

// 	lst = NULL;
// 	ft_lstadd_back(&lst, ft_lstnew("Miku"));
// 	ft_lstadd_back(&lst, ft_lstnew("is"));
// 	ft_lstadd_back(&lst, ft_lstnew("cute"));

// 	test_remove(ft_lsttoaa(lst, map_copy), "not", NULL);
// 	ft_lstadd_front(&lst, ft_lstnew("not"));

// 	test_remove(ft_lsttoaa(lst, map_copy), "not", NULL);
// 	ft_lstadd_front(&lst, ft_lstnew("not"));

// 	test_remove(ft_lsttoaa(lst, map_copy), "not", NULL);
// 	ft_lstadd_back(&lst, ft_lstnew("not"));

// 	test_remove(ft_lsttoaa(lst, map_copy), "not", NULL);
// 	ft_lstclear(&lst, NULL);
// 	system("leaks -q test.miku");
// }

int	main(void)
{
	ft_printf("upper: %c lower: %c\n", ft_toupper('a'), ft_tolower('A'));
}
