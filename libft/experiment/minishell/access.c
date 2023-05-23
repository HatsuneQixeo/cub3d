#include "libft.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	while (*++argv != NULL)
// 	{
// 		printf("accessingF: (%s) result in (%d)\n", *argv, access(*argv, F_OK));
// 		perror("access");
// 		printf("errno: %d\n", errno);
// 		printf("accessingX: (%s) result in (%d)\n", *argv, access(*argv, X_OK));
// 		perror("access");
// 		printf("errno: %d\n", errno);
// 		printf("accessingFX: (%s) result in (%d)\n", *argv, access(*argv, F_OK | X_OK));
// 		perror("access");
// 		printf("errno: %d\n", errno);
// 	}
// }

int	main(int argc, char **argv)
{
	const char	*path = argv[1];

	printf("path: %s\n", path);
	if (access(path, F_OK) == -1)
		perror(path);
	if (access(path, F_OK | X_OK) == -1)
		perror(path);
	(void)argc;
}
