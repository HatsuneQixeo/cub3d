#include "cub3d.h"
#include "element.h"

int	cubmap_parse_texture(void *p_mlx, const t_list *lst_elements,
		t_texture *texture);

char	*ft_strfind_if(const char *str, t_ftis ft_is)
{
	while (*str != '\0' && !ft_is(*str))
		str++;
	if (!ft_is(*str))
		return (NULL);
	return ((char *)str);
}

static t_element	*parse_element(const char *line)
{
	const char	*delimiter = ft_strfind_if(line, ft_isspace);

	if (delimiter == NULL)
		return (element_new(ft_strdup(line), ft_strdup("")));
	else
		return (element_new(ft_substr(line, 0, delimiter - line),
				ft_strdup(ft_strskip_is(delimiter, ft_isspace))));
}

static void	getmap_lexer(char **strlist, t_list **lst_element, t_map *map)
{
	const char		*line;
	unsigned int	i;

	i = -1;
	while (strlist[++i] != NULL)
	{
		line = strlist[i];
		if (stris_empty(line) || stris_only(line, ft_isspace))
			continue ;
		if (ft_isspace(line[0]) || ft_isdigit(line[0]))
			break ;
		ft_lstadd_back(lst_element, ft_lstnew(parse_element(line)));
	}
	map->layout = ft_strlistpad(&strlist[i], ft_strpad_right, Void);
	map->size.y = ft_strcount(map->layout);
	if (map->size.y != 0)
		map->size.x = ft_strlen(map->layout[0]);
}

int	cubmap_valid_size(const t_map map)
{
	const char	*msg;

	if (!(map.size.y != 0 && map.size.x != 0))
		msg = "Empty Map";
	else if (!(map.size.y >= 3 && map.size.x >= 3))
		msg = "Map too small";
	else
		return (0);
	ft_dprintf(2, "Error\n%s\n", msg);
	return (-1);
}

int	cubmap_getmap(void *p_mlx, const char *path, t_map *map, t_texture *texture)
{
	char **const	file_content = ft_readfile(path);
	t_list			*lst_element;
	int				status;

	if (file_content == NULL)
	{
		ft_putendl_fd("Error", 2);
		perror(path);
		return (-1);
	}
	lst_element = NULL;
	getmap_lexer(file_content, &lst_element, map);
	ft_strlistclear(file_content);
	status = cubmap_parse_texture(p_mlx, lst_element, texture);
	if (status != -1)
		status = cubmap_valid_size(*map);
	if (status != -1)
		status = -(cubmap_valid_door(*map)
				+ cubmap_valid_unit(*map)
				+ cubmap_surrounded(*map) < 0);
	ft_lstclear(&lst_element, element_del);
	if (status == -1)
		ft_strlistclear(map->layout);
	return (status);
}
