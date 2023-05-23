#include "libft.h"

char	*ft_strchr_set(const char *str, const char *set)
{
	if (*set ==  '\0')
		return ((char *)str);
	str--;
	while (*++str != '\0')
		if (ft_strchr(set, *str))
			return ((char *)str);
	return (0);
}

void	ft_strdelchr(char *str, char c)
{
	char	*it;

	it = --str;
	while (*++str != '\0')
	{
		if (*str != c)
			*++it = *str;
	}
	*it = '\0';
}

char	*ft_strfilter(const char *src, char c)
{
	char	*str;
	size_t	i;

	str = malloc(ft_strlen(src) - ft_strcount_chr(src, c) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*src != '\0')
	{
		if (*src != c)
			str[i++] = *src;
		src++;		
	}
	str[i] = '\0';
	return (str);
}
