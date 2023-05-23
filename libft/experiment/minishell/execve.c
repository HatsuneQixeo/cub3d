#include "libft.h"

int	main(void)
{
	// Absolute path?
	#define HOMEDIR	"/Users/hqixeo/"
	// Directory
	execve(HOMEDIR, NULL, NULL);
	ft_printf("accessF: %d\n", access(HOMEDIR, F_OK));
	ft_printf("accessX: %d\n", access(HOMEDIR, X_OK));
	perror(HOMEDIR);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	printf("argv[0]: %s\n", *argv);
// 	printf("envp[0]: %s\n", *envp);
// }
// int	main(int argc, char **argv, char **envp)
// {
// 	execve("aaa", NULL, NULL);
// }
