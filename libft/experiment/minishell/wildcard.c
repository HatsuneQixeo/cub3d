#include "libft.h"
#include <dirent.h>

void	showdir(void *dirent)
{
	const struct dirent	*pdirent = dirent;

	printf("ino: %llu\n", (uint64_t)pdirent->d_ino);			/* file number of entry */
	printf("seekoff: %llu\n", (uint64_t)pdirent->d_seekoff);	/* seek offset (optional, used by servers) */
	printf("reclen: %u\n", (uint16_t)pdirent->d_reclen);		/* length of this record */
	printf("namelen: %u\n", (uint16_t)pdirent->d_namlen);		/* length of string in d_name */
	printf("type: %u\n", (uint8_t)pdirent->d_type);			/* file type, see below */
	printf("name: %s\n", (char *)pdirent->d_name);				/* entry name (up to MAXPATHLEN{1024 (+1 depends on os?)} bytes) */
	printf("\n");
}

char	**dir_content(const char *path)
{
	t_list			*lst_buffer;
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(path);
	lst_buffer = NULL;
	if (dir == NULL)
	{
		perror(path);
		return (NULL);
	}
	while (1)
	{
		dirent = readdir(dir);
		if (dirent == NULL)
			break ;
		// showdir(dirent);
		ft_lstadd_back(&lst_buffer, ft_lstnew(dirent->d_name));
	}
	closedir(dir);
	return ((char **)ft_lsttoaa_clear(&lst_buffer));
}

int	wildcard_substitution(t_list *lst_pattern, const char *str)
{
	const char	*find;

	if (cmp_strprefix(str, lst_pattern->content))
		return (-1);
	if (lst_pattern->next == NULL)
		return (0);
	find = &str[ft_strlen(lst_pattern->content)];
	lst_pattern = lst_pattern->next;
	while (lst_pattern->next != NULL)
	{
		find = ft_strstr(find, lst_pattern->content);
		if (find == NULL)
			return (-1);
		find += ft_strlen(lst_pattern->content);
		lst_pattern = lst_pattern->next;
	}
	if (cmp_strsuffix(find, lst_pattern->content))
		return (-1);
	return (0);
}

char	**wildcard(t_list *lst_pattern)
{
	char	**strlist_content;

	strlist_content = dir_content(".");
	if (lst_pattern == NULL)
		return (strlist_content);
	if (((const char *)lst_pattern->content)[0] != '.')
		ft_aaremove((void **)strlist_content, cmp_strprefix, ".", NULL);
	for (unsigned int i = 0; strlist_content[i] != NULL; i++)
	{
		const char	*colour;

		if (wildcard_substitution(lst_pattern, strlist_content[i]) == -1)
			colour = RED;
		else
			colour = GREEN;
		ft_printf("%s%-18s\n"DEF, colour, strlist_content[i]);
	}
	free(strlist_content);
	return (NULL);
}

t_list	*wildcard_lexer(const char *str)
{
	const char	*wildcard = ft_strchr(str, '*');
	t_list		*lst_pattern;

	lst_pattern = NULL;
	while (wildcard != NULL)
	{
		ft_lstadd_back(&lst_pattern, ft_lstnew(ft_substr(str, 0, wildcard - str)));
		str = wildcard + 1;
		wildcard = ft_strchr(str, '*');
	}
	ft_lstadd_back(&lst_pattern, ft_lstnew(ft_strdup(str)));
	return (lst_pattern);
}

int	main(int argc, char **argv)
{
	char	**strlist_matched;
	t_list	*lst_pattern;

	lst_pattern = NULL;
	if (argc == 1)
	{
		/* Any (non hidden) */
		ft_lstadd_back(&lst_pattern, ft_lstnew(""));

		/* with . prefix only (include hidden) */
		// ft_lstadd_back(&lst_pattern, ft_lstnew("."));

		/* . suffix */
		// ft_lstadd_back(&lst_pattern, ft_lstnew(""));
		// ft_lstadd_back(&lst_pattern, ft_lstnew("."));

		/* Same, prefix */
		// ft_lstadd_back(&lst_pattern, ft_lstnew("."));
		// ft_lstadd_back(&lst_pattern, ft_lstnew(""));
	}
	else
	{
		// while (*++argv != NULL)
		// 	ft_lstadd_back(&lst_pattern, ft_lstnew(*argv));
		lst_pattern = wildcard_lexer(argv[1]);
		ft_lstiter(lst_pattern, iter_showstr);
	}
	strlist_matched = wildcard(lst_pattern);
	if (strlist_matched != NULL)
		ft_strlistiteri(strlist_matched, iteri_showstr);
	system("leaks -q wildcard.miku");
}
