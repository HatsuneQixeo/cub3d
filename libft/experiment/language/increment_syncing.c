#include <stdio.h>

int	main(void)
{
	int	n;

	n = 1;
	while (++n && n++ && n++ < 100)// ??????
		printf("%d\n", n);
}
