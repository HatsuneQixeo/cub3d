#include "libft.h"
#include <math.h>

//colour is saved as rgba with 4 individual byte in integer data type
// int	main(void)
// {
// 	unsigned int	colour;
// 	size_t			i;

// 	colour = VALUE_T;
// 	for (i = 0; i <= 256; i++)
// 	{
// 		colour = VALUE_T * i;
// 		// ft_memprint(&colour, 4);
// 		ft_printf("\n");
// 		ft_printf("%u\n", colour);
// 		ft_printf("diff: %u\n", colour - (VALUE_T * (i - 1)));
// 	}
// }

//memory and bytes
// int	main(void)
// {
// 	int	nbr;
// 	char	*str;

// 	nbr = 256 * 256 * 65;
// 	ft_printf("memchr: %s\n", memchr(&nbr, 65, 4));
// 	ft_printf("ft_memchr: %s\n", ft_memchr(&nbr, 65, 4));
// 	for (unsigned char c = 0; c < 255; c++)
// 	{
// 		str = ft_utoa_base(c, "01");
// 		ft_printf("c: %3d; str: %08s\n", c, str);
// 		free(str);
// 	}
// 	str = ft_utoa_base(255, "01");
// 	ft_printf("c: %3d; str: %08s\n", 255, str);
// 	free(str);
// 	for (unsigned short int uu = 0; uu < (unsigned short int)-1; uu++)
// 	{
// 		ft_printf("nbr: %d\n", uu);
// 		ft_memprint(&uu, sizeof(uu), sizeof(uu));
// 	}
// }

// int	main(void)
// {
// 	char	*ptr;
// 	int		len;

// 	len = 6;
// 	ptr = malloc(len);
// 	ptr[len - 1] = 0;
// 	unsigned long	*nbr;

// 	nbr = (void *)ptr;
// 	*nbr = 77 + (256 * 105) + (256 * 256 * 107) + (256 * 256 * 256 * 117) + ((unsigned long)(256 * 256 * 256) * 256 * 62);
// 	ft_printf("%s\n", ptr);
// }

/* Wonders inside null next */
// int	main(void)
// {
// 	t_list	*lst_ts;

// 	lst_ts = ft_lstnew("");
// 	ft_printf("Before moving into next\n");
// 	ft_printf("%-15s: %p\n", "	lst_ts->next", lst_ts->next);
// 	ft_printf("%-15s: %p\n", "	&lst_ts->next", &lst_ts->next);

// 	lst_ts = lst_ts->next;
// 	ft_printf("After moving into next\n");
// 	ft_printf("%-15s: %p\n", "	lst_ts", lst_ts);
// 	ft_printf("%-15s: %p\n", "	&lst_ts->content", &lst_ts->content);
// 	ft_printf("%-15s: %p\n", "	&lst_ts->next", &lst_ts->next);
// }

/* Handling potential malloc error for strlist
	@remark How should the conversion function react to NULL return value
*/
// int	main(void)
// {
// 	t_list	*lst;
// 	char	**strlist;

// 	lst = ft_lstnew(ft_strdup("Hatsune"));
// 	ft_lstadd_back(&lst, ft_lstnew(" "));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("Miku")));
// 	lst->next->content = 0;
// 	strlist = ft_lsttoaa_clear(&lst);
// 	ft_putstrlist_fd(strlist, 1);
// 	ft_strlistclear(strlist);
// 	strlist = 0;
// 	system("leaks -q test.miku");
// }
