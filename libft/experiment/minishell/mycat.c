#include "libft.h"

int	main(void)
{
	while (1)
	{
		char	*input = get_next_line(0);

		ft_dprintf(2, "input: ");
		if (input == NULL)
		{
			ft_dprintf(2, "mycat: eof\n");
			break ;
		}
		ft_dprintf(2, "writing: %s", input);
		if (ft_printf("%s", input) < 0)
			perror("mycat");
		free(input);
	}
}
// experiment/mycat.miku
