#include "exlib.h"

void	showpad(char **strlist, t_ftstrpad ft_strpad)
{
	char **const	padded = ft_strlistpad(strlist, ft_strpad, ' ');

	printf("padded: %p\n", padded);
	ft_strlistiteri(padded, iteri_showstr);
	ft_strlistclear(padded);
}

int	main(int argc, char **argv)
{
	showpad(argv + 1, ft_strpad_left);
	showpad(argv + 1, ft_strpad_right);
	if (!SAN)
		system("leaks -q strlistpad.miku");
	(void)argc;
}
