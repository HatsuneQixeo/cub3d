#include "cub3d.h"

void	cub3d_runtime_assertion(const int condition, const char *attachment)
{
	if (condition)
		return ;
	ft_putendl_fd("Error", 2);
	perror(attachment);
	exit(1);
}
