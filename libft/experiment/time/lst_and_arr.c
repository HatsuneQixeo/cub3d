#include "libft.h"
#include <sys/time.h>

#ifndef SIZE
# define SIZE	10000
#endif

/* Future Test:
	* Time taken in iterating linked list and array
*/

typedef void *(*t_fttime)(void *arg);

/**
 * @brief Utils
 */

char	*ft_newyear_newmiku(void)
{
	return (ft_strdup("Hatsune Miku"));
}

/**
 * @brief Creat
 */

void	*creat_resize(void *null)
{
	char	**strlist;

	strlist = NULL;
	for (int i = 0; i < SIZE; i++)
	{
		const int	size_strlist = ft_strcount(strlist);
		char		**new;

		new = malloc((size_strlist + 1 + 1) * sizeof(char *));
		ft_memcpy(new, strlist, size_strlist * sizeof(char *));
		new[size_strlist] = ft_newyear_newmiku();
		new[size_strlist + 1] = NULL;
		free(strlist);
		strlist = new;
	}
	return (strlist);
	(void)null;
}

void	*creat_addback(void *null)
{
	t_list	*lst;

	lst = NULL;
	for (int i = 0; i < SIZE; i++)
		ft_lstadd_back(&lst, ft_lstnew(ft_newyear_newmiku()));
	return (lst);
	(void)null;
}

void	*creat_addfront(void *null)
{
	t_list	*lst;

	lst = NULL;
	for (int i = 0; i < SIZE; i++)
		ft_lstadd_front(&lst, ft_lstnew(ft_newyear_newmiku()));
	return (lst);
	(void)null;
}

/**
 * @brief Clean
 */

void	*clean_lst(void *lst)
{
	ft_lstclear((t_list **)lst, free);
	return (NULL);
}

void	*clean_lstnode(void *lst)
{
	ft_lstclear((t_list **)lst, NULL);
	return (NULL);
}

void	*clean_arr(void *arr)
{
	ft_strlistclear(*(char ***)arr);
	return (NULL);
}

/**
 * @brief Test wrap
 */

void	*timetakes(t_fttime ft, void *arg)
{
	struct timeval	start, end;
	double			time;
	void			*ret;

	gettimeofday(&start, NULL);
	ret = ft(arg);
	gettimeofday(&end, NULL);
	time = (end.tv_sec - start.tv_sec) * 1000
		+ (double)(end.tv_usec - start.tv_usec) / 1000;
	printf(": %.3f\n", time);
	return (ret);
}

void	test_creat_clean(t_fttime creat, t_fttime clean)
{
	void	*data;

	data = timetakes(creat, NULL);
	printf("Clean	");
	timetakes(clean, &data);
	printf("\n");
}


/**
 * @brief Dup
 */

void	*lstdup_shallow(void *arg)
{
	t_list	*lst;
	t_list	*lst_dup;

	lst = arg;
	lst_dup = NULL;
	while (lst != NULL)
	{
		ft_lstadd_front(&lst_dup, ft_lstnew(map_copy(lst->content)));
		lst = lst->next;
	}
	return (lst_dup);
}

void	*lstdup_deep(void *arg)
{
	t_list	*lst;
	t_list	*lst_dup;

	lst = arg;
	lst_dup = NULL;
	while (lst != NULL)
	{
		ft_lstadd_front(&lst_dup, ft_lstnew(map_strdup(lst->content)));
		lst = lst->next;
	}
	return (lst_dup);
}

/**
 * @brief Main
 */
int	main(void)
{
	// printf("Just dealing with the delay");
	// test_creat_clean(creat_resize, clean_arr);
	
	// printf("creat_ADDFRONT	");
	// test_creat_clean(creat_addfront, clean_lst);

	printf("creat_ADDBACK	");
	test_creat_clean(creat_addback, clean_lst);

	// printf("creat_RESIZE	");
	// test_creat_clean(creat_resize, clean_arr);
// Deep and shallow
	{
		// void	*data;
		// void	*data_dup;

		// printf("creat_addfront");
		// data = timetakes(creat_addfront, NULL);
		// printf("shallow copy");
		// data_dup = timetakes(lstdup_shallow, data);
		// printf("clean shallow");
		// timetakes(clean_lstnode, &data_dup);
		// printf("clean deep");
		// timetakes(clean_lst, &data);

		// printf("creat_addfront");
		// data = timetakes(creat_addfront, NULL);
		// printf("deep copy");
		// data_dup = timetakes(lstdup_deep, data);
		// printf("clean deep");
		// timetakes(clean_lst, &data_dup);
		// printf("clean deep");
		// timetakes(clean_lst, &data);
	}
	char	buffer[1024];

	snprintf(buffer, sizeof(buffer), "leaks -q %d >&2", getpid());
	system(buffer);
}
