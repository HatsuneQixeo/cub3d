#include "libft.h"

void	ft_lstremove(t_list **lst, t_list *node, t_ftdel del);

// void	ft_lstpop(t_list **lst, t_ftdel del)
// {
// 	t_list	*pop;

// 	pop = *lst;
// 	ft_printf("freeing: %s\n", pop->content);
// 	(*lst) = (*lst)->next;
// 	ft_lstdelone(pop, del);
// }

// int	main(void)
// {
// 	t_list	*lst;

// 	lst = NULL;
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("Hatsune Miku")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("is")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("cute")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
// 	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
// 	ft_lstiter(lst, show_address);
// 	for (t_list *it = lst; it != NULL; )
// 	{
// 		t_list	*next = it->next;
// 		if (!ft_strcmp(it->content, "not"))
// 			ft_lstremove(&lst, it, free);
// 		it = next;
// 	}
// 	ft_printf("\n");
// 	ft_lstremove(&lst, NULL, free);
// 	ft_lstremove(&lst, (void *)1, free);
// 	ft_lstiter(lst, show_str);
// 	ft_lstiter(lst, show_address);
// 	ft_lstclear(&lst, free);
// }

int	cmp_strcmp(const void *str1, const void *str2)
{
	return (ft_strcmp(str1, str2));
}

int	main(void)
{
	t_list	*lst;

	lst = NULL;
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("Hatsune Miku")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("is")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("cute")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
	ft_lstadd_back(&lst, ft_lstnew(ft_strdup("not")));
	ft_lstremoveif(&lst, "not", cmp_strcmp, free);
	ft_lstiter(lst, iter_showstr);
	system("leaks -q lstremove.miku");
}
