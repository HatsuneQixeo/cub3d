#include "libft.h"

/* Index shenanigans
	Think I found this too in a cpp tutorial
*/
int main(void)
{
	char *str = strdup("1bcde");

	printf("%c\n", str[2]);
	printf("%c\n", *(str + 2));
	printf("%c\n", *(2 + str));
	printf("%c\n", 2[str]);
	printf("%c\n", 3[str]);
	printf("%c\n", 4[str]);
	printf("%c\n", *str + 2);
}
