#include "player.h"

typedef struct s_pair
{
	char	c;
	t_point	direction;
}			t_side_pair;

static t_player	player_init(const t_point pos, const char orientation)
{
	const t_side_pair	arr[] = {
	{.c = StartUp, .direction = {.x = 0, .y = -1}},
	{.c = StartLeft, .direction = {.x = -1, .y = 0}},
	{.c = StartDown, .direction = {.x = 0, .y = 1}},
	{.c = StartRight, .direction = {.x = 1, .y = 0}}
	};
	const unsigned int	length = (sizeof(arr) / sizeof(arr[0]));
	t_player			player;
	unsigned int		i;

	i = 0;
	while (i < length && arr[i].c != orientation)
		i++;
	ft_assert(i != length, "player_init: Invalid orentation character");
	player.pos = point_add(pos, (t_point){.5, .5});
	player.dir = arr[i].direction;
	return (player);
}

int	cubmap_player_init(const t_map map, t_player *player)
{
	t_list			*lst_player;
	const t_point	*pos;
	int				status;

	lst_player = cubmap_gather_if(map, cubmap_isplayer);
	status = -1;
	if (lst_player == NULL)
		ft_putendl_fd("Error\nMissing Player", 2);
	else if (lst_player->next != NULL)
		cubmap_showlsterror(map, lst_player, "Duplicate Players");
	else
		status = 0;
	pos = lst_player->content;
	*player = player_init(*pos, map.layout[(int)pos->y][(int)pos->x]);
	ft_lstclear(&lst_player, point_del);
	return (status);
}
