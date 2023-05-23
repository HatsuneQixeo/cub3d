#include "libft.h"

/**
 * @brief Turn any linked list into array
 * 
 * @attention
 * Question: How should the NULL content be interpreted?
 * @attention
 * 1) I can create a function to exclude all the NULL content to replace lstsize
 * , and skip over the NULL content in loop.
 * 	This could potentially result in a few problem,
 * 	such as unsynced size with the outer variable
 * A safer option would be to let this function set a new given variable to the array size with pointer
 * 	This approach is result in the most accurate representation of the original list,
 * 	in a sense that NULL content is completely excluded
 * @attention
 * 2) I can exclude the NULL content in loop but retain the original size of the lst
 * @attention
 * 3) I can set it as empty struct similar to calloc (In use)
 * 
 * @param lst The linked list
 * @param sizeof_datatype sizeof(t_datatype)
 * @return void* The converted array
 * 
 * @note Due to the attributes of array, there's no null terminating end.
 * @note This is a deep copy
 */
void	*ft_lstto_anyarray(t_list *lst, size_t sizeof_datatype)
{
	void	*array;
	int		y;

	array = malloc(sizeof_datatype * (ft_lstsize(lst)));
	if (array == NULL)
		return (NULL);
	y = 0;
	while (lst != NULL)
	{
		if (lst->content == NULL)
			ft_bzero(array + y, sizeof_datatype);
		else
			ft_memcpy(array + y, lst->content, sizeof_datatype);
		y += sizeof_datatype;
		lst = lst->next;
	}
	return (array);
}

struct MikuIdealPartner
{
	char	*name;
	int		age;
	int		height;
	int		weight;
	int		haircolour;
	int		hairlength;
};

struct MikuIdealPartner	*newyear_newme(int aging)
{
	struct MikuIdealPartner	*ofc_its_me;

	ofc_its_me = malloc(sizeof(struct MikuIdealPartner));
	ofc_its_me->name = "Qixeo";
	ofc_its_me->age = 39 + aging;
	ofc_its_me->height = (int)(39
		+ (831 / 39) + (831 / 39) + (831 / 39)
		+ (831 / 39) + (831 / 39) + (831 / 39));
	ofc_its_me->weight = (int)(39 + (39 / 39)
		+ (39 / 39) + (39 / 39) + (39 / 39)
		+ (39 / 39) + (39 / 39) + (39 / 39)
		+ (39 / 39) + (39 / 39) + (39 / 39));
	ofc_its_me->haircolour = 0x393939;
	ofc_its_me->hairlength = 39;
	return (ofc_its_me);
}

void	showme(struct MikuIdealPartner *me)
{
	printf("Name: %s\n", me->name);
	printf("age: %d\n", me->age);
	printf("height: %d\n", me->height);
	printf("weight: %d\n", me->weight);
	printf("haircolour: %X\n", me->haircolour);
	printf("hairlength: %d\n", me->hairlength);
	printf("\n");
}

int	main(void)
{
	t_list	*lst;

	lst = NULL;
	/* Initialization */
	for (int i = 0; i < 10; i++)
		ft_lstadd_front(&lst, ft_lstnew(newyear_newme(i)));

	printf("Showing linked list:\n");
	for (t_list *it = lst; it != NULL; it = it->next)
		showme(it->content);
	printf("\n");

	struct MikuIdealPartner	*alotofme = ft_lstto_anyarray(lst, sizeof(struct MikuIdealPartner));

	/* Uh oh, There's no null terminating character for non character array */
	printf("Showing array:\n");
	for (int i = 0; i < 10; i++)
		showme(alotofme + i);
	printf("\n");

	// struct MikuIdealPartner	**dd;

	// dd[0]->age;
	ft_lstclear(&lst, free);
	free(alotofme);
	system("leaks -q lsttoany.miku >&2");
}
