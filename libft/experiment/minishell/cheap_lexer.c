#include "libft.h"

/**
 * @brief Have the same basic functionality with split
 * But contain each delimiter string between splitted arguments
 * @param src 
 * @param set 
 * @return char** Splitted strlist
 */
char	**ft_savesplit_set(const char *src, const char *set)
{
	t_list	*lst;
	size_t	len;

	if (src == NULL)
		return (NULL);
	lst = NULL;
	while (*src != '\0')
	{
		len = 0;
		while (src[len] != '\0' && ft_strchr(set, src[len]))
			len++;
		if (len)
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(src, 0, len)));
		src += len;
		len = 0;
		while (src[len] != '\0' && !ft_strchr(set, src[len]))
			len++;
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(src, 0, len)));
		src += len;
	}
	ft_lstiter(lst, show_str);
	return (ft_lsttoaa_clear(&lst));
}

int	unclosed_end(char *ptr, char open, char end)
{
	char	*ptr_open;
	char	*ptr_end;

	ptr_open = ft_strchr(ptr, open);
	if (ptr_open == NULL)
		return (0);
	while (ptr_open != NULL)
	{
		ptr_end = ft_strchr(ptr_open + 1, end);
		if (ptr_end == NULL)
			return (1);
		ptr_open = ft_strchr(ptr_end + 1, open);
	}
	return (0);
}

void	joinquote(char **strlist, char open, char end)
{
	strlist--;
	while (*++strlist != NULL)
	{
		while (*(strlist + 1) != NULL && unclosed_end(*strlist, open, end))
		{
			*strlist = ft_strcombine(*strlist, *(strlist + 1));
			ft_memmove(strlist + 1, strlist + 2,
				sizeof(char *) * (ft_strcount(strlist + 2) + 1));
		}
	}
}

/**
 * @brief Failed attempt
 * 
 * 
 * @bug Unable to comprehend the context with ' and " at the same time
 * 	Not gonna spend my time fixing this, not worth it
 */
void	testsavesplit(const char *str, const char *set)
{
	char	**strlist;

	strlist = ft_savesplit_set(str, set);
	ft_printf("SAVESPLITTEST\n");
	ft_printf("str:	%s\n", str);
	ft_printf("set:	%s\n", set);
	ft_strlistiteri(strlist, iteristr_showstr);
	joinquote(strlist, '\"', '\"');
	ft_printf("join doublequote: \n");
	ft_strlistiteri(strlist, iteristr_showstr);
	joinquote(strlist, '\'', '\'');
	ft_printf("join singlequote: \n");
	ft_strlistiteri(strlist, iteristr_showstr);
	ft_strlistclear(strlist);
}

int	main(void)
{
	// Clutterd
	// testsavesplit("echo $MIKUout>$MIKU$MIKUpipe|$MIKUinfile<$MIKUheredoc<<$MIKU>>$MIKUappend", "<|>");
	// Space
	// testsavesplit("echo $MIKU out > $MIKU$MIKUpipe | $MIKUinfile < $MIKUheredoc << $MIKU >> $MIKUappend", "<|>");
	// Quote
	// testsavesplit("echo \"$MIKU out > $MIKU$MIKUpipe\" | $MIKUinfile < $MIKUheredoc << $MIKU >> $MIKUappend", "<|>");
	// 2 quote
	// testsavesplit("echo \"$MIKU out >\" $MIKU$MIKUpipe\" | $MIKUinfile \"< $MIKUheredoc << $MIKU >> $MIKUappend", "<|>");
	// quoting
	testsavesplit("echo '1$MIKU out >1' '2$MIKU2''3$MIKU3'pipe'4 | 4'$MIKU'5infile 5'< '6$MIKU6'heredoc'7 << $7'MIKU >> $'8MIKUapp8'end", "<|>");
	// char	buffer[1024];

	// snprintf(buffer, sizeof(buffer), "leaks -q %d", getpid());
	// system(buffer);
}
