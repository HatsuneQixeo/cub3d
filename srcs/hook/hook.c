#include "hook.h"
#include "libft.h"

int	hook_button_close(const int keycode, const int status)
{
	ft_putendl_fd("Game Closed", 2);
	exit(status);
	return (0);
	(void)keycode;
}
