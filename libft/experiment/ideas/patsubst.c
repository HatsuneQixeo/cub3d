#include "libft.h"
/* Aka losersed? */

char	*ft_patsubst(const char *str, const char *replace, const char *with)
{
	t_list			*lst_buffer;
	const char		*find = ft_strstr(str, replace);
	const size_t	len_replace = ft_strlen(replace);

	if (len_replace == 0)
		return (ft_strdup(str));
	lst_buffer = NULL;
	while (find != NULL)
	{
		ft_lstadd_back(&lst_buffer, ft_lstnew(ft_substr(str, 0, find - str)));
		str = find + len_replace;
		find = ft_strstr(str, replace);
	}
	ft_lstadd_back(&lst_buffer, ft_lstnew(ft_strdup(str)));
	return (ft_lsttostr_delimiter_clear(&lst_buffer, with));
}
