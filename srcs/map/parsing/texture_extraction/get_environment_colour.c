#include "element.h"
#include "colour.h"

static t_list	*convert_core(char **strlist_values, t_colour_byte arr[4])
{
	unsigned int	i;
	long			value;
	t_list			*lst_err;

	lst_err = NULL;
	i = ft_strcount(strlist_values);
	while (i--)
	{
		if (!stris_numeric(strlist_values[i]))
			ft_lstadd_front(&lst_err, ft_lstnew(
					ft_strjoin("Invalid value: ", strlist_values[i])));
		else
		{
			if (ft_atol_range(strlist_values[i], &value, 0, UCHAR_MAX) == -1)
				ft_lstadd_front(&lst_err, ft_lstnew(
						ft_strjoin("Value out of range: ", strlist_values[i])));
			else
				arr[i] = value;
		}
	}
	return (lst_err);
}

static int	colour_convert(char **strlist_values, t_colour *colour)
{
	t_colour_byte	arr[4];
	t_list			*lst_err;

	lst_err = convert_core(strlist_values, arr);
	if (lst_err == NULL)
	{
		*colour = colour_from_rgba(arr[0], arr[1], arr[2], arr[3]);
		return (0);
	}
	ft_putendl_fd("Error", 2);
	ft_lstiter(lst_err, iter_puterrendl);
	ft_lstclear(&lst_err, free);
	return (-1);
}

static int	ft_strtocolour(const char *properties, t_colour *colour)
{
	const unsigned int	expected_amount = 3;
	char **const		strlist_values = ft_split(properties, ',');
	const unsigned int	len = ft_strcount(strlist_values);
	int					status;

	status = -1;
	if (len != expected_amount)
		ft_dprintf(2, "Error\nExpected %.*s value: %s\n",
			expected_amount + (expected_amount - 1), "R,G,B,A", properties);
	else
		status = colour_convert(strlist_values, colour);
	ft_strlistclear(strlist_values);
	return (status);
}

int	get_environment_colour(t_element_table element_table,
			t_colour *ceiling, t_colour *floor)
{
	const t_element	*ele_floor = element_table[IdxElemFloor]->content;
	const t_element	*ele_ceiling = element_table[IdxElemCeiling]->content;
	const char		*str_floor = ele_floor->properties;
	const char		*str_ceiling = ele_ceiling->properties;

	return (ft_strtocolour(str_floor, floor)
		+ ft_strtocolour(str_ceiling, ceiling));
}
