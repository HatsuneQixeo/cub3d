#include "cubmap.h"

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

t_player	cubmap_getplayer(const t_map map)
{
	t_point	it;

	it.y = -1;
	while (++it.y < map.size.y)
	{
		it.x = -1;
		while (++it.x < map.size.x)
		{
			if (cubmap_isplayer(&map, it))
				return (player_init(it, map.layout[(int)it.y][(int)it.x]));
		}
	}
	return ((t_player){0});
}
