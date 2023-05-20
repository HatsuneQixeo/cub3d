#include "element.h"
#include "colour.h"

static int	colour_convert(char **strlist_values, t_colour *colour)
{
	t_colour_byte	arr[4];
	int				ret;
	unsigned int	i;
	long			value;

	ft_bzero(arr, sizeof(arr));
	ret = 0;
	i = -1;
	while (strlist_values[++i] != NULL)
	{
		if (!stris_numeric(strlist_values[i]))
			ret = ft_dprintf(2, "Invalid value: %s\n", strlist_values[i]);
		else
		{
			/* Still not protected, atoi/atol itself needs to report error */
			value = ft_atol(strlist_values[i]);
			if (!(0 <= value && value <= UCHAR_MAX))
				ret = ft_dprintf(2, "Value out of range: %s\n", strlist_values[i]);
			else
				arr[i] = value;
		}
	}
	if (ret != 0)
		return (-1);
	*colour = colour_from_rgba(arr[0], arr[1], arr[2], arr[3]);
	return (0);
}

static int	ft_strtocolour(const char *properties, t_colour *colour)
{
	const unsigned int	expected_len = 3;
	char **const		strlist_values = ft_split(properties, ',');
	const unsigned int	len = ft_strcount(strlist_values);
	int					ret;

	ret = -1;
	/* Testing required */
	if (len != expected_len)
		ft_dprintf(2, "Expected %.*s value: %s\n",
			expected_len + (expected_len - 1), "R,G,B,A", properties);
	else
		ret = colour_convert(strlist_values, colour);
	ft_strlistclear(strlist_values);
	return (ret);
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
