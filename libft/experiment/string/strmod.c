#include "libft.h"

#define TESTSTR	"Not 'str'string''string'ing'"
#define TESTRM	"'string'"

char	*strmod_rmsubstr(const char *str, const char *str_rm);

int	main(void)
{
	char	*str;

	str = strmod_rmsubstr(TESTSTR, TESTRM);
	printf("str: %s\n", str);
	free(str);
}
