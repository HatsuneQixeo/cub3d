#include "exlib.h"

// int	main(void)
// {
// 	const char	*str_qixeolovemiku = "Qixeo love Hatsune Miku";
// 	const char	*catmiku = "Miku: meow";

// 	printf("__STRING(%s): %s\n", __STRING(str_qixeolovemiku), str_qixeolovemiku);
// 	printf("__CONCAT(%s)\n", __CONCAT(cat, miku)); /* No idea what's this for */
// 	printf("__P(%s)\n", __P(str_qixeolovemiku)); /* No idea what's this for */
// 	__IDSTRING(mikuname, "mikustr"); /* Declare a static const string(char []), using macro?
// 								There seem's to somethinig with __used macro too */
// 	printf("name: %s\n", mikuname);
// }

int	main(void)
{
	printf("ret: %d\n", TIME("Miku", printf("Hatsune Miku")));
}
