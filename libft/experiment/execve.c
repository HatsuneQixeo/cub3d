#include "libft.h"

int	main(int argc, char **argv, char **envp)
{
	iteri_name("argv");
	ft_strlistiteri(argv, iteri_showstr);
	iteri_name("envp");
	ft_strlistiteri(envp, iteri_showstr);
	(void)argc;
}
