#include "cub3d.h"
#include "element.h"

int	cub3d_get_texture(void *p_mlx, const t_list *lst_elements, t_texture *texture);

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

/**
 * Question: What should this function even return
 * Hâtsūñè Mīkù
 */
void	cub3d_parsecontent(char **strlist, t_list **lst_element,
			char ***map_layout)
{
	const char		*line;
	unsigned int	i;

	i = -1;
	while (strlist[++i] != NULL)
	{
		line = strlist[i];
		if (!stris_empty(line) || stris_only(line, ft_isspace))
			continue ;
		/* Check if it's map start */
		if (ft_isspace(line[0]) || ft_isdigit(line[0]))
			break ;
		ft_lstadd_back(lst_element, ft_lstnew(parse_element(line)));
	}
	*map_layout = ft_strlistdup(&strlist[i]);
}

int	cubmap_getmap(const char *path, t_game *game)
{
	char **const	file_content = ft_readfile(path);
	t_list	*lst_element;
	t_map	map;
	int		status;

	if (file_content == NULL)
	{
		perror(path);
		return (-1);
	}
	lst_element = NULL;
	ft_bzero(&map, sizeof(map));
	cub3d_parsecontent(file_content, &lst_element, &map.layout);
	status = cub3d_get_texture(game->mlx.p_mlx, lst_element, &game->texture);
	if (status != -1)
		status = (cubmap_valid_player(map)
			+ cubmap_valid_unit(map)
			+ cubmap_surrounded(map)) < 0;
	ft_lstclear(&lst_element, element_del);
	ft_strlistclear(file_content);
	return (-status);
}
