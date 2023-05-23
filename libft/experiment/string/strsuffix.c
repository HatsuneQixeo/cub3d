#include "libft.h"
#define SHOW(str)	ft_dprintf(2, #str": [%s]\n", str)

int	restrcmp(const char *str1, const char *str2)
{
	const char	*end1 = ft_strchr(str1, '\0');
	const char	*end2 = ft_strchr(str2, '\0');

	while (*end1 == *end2 && end1 != str1 && end2 != str2)
	{
		end1--;
		end2--;
	}
	return ((unsigned char)*end1 - (unsigned char)*end2);
}

void	ft_strreverse(char *str)
{
	char	*str_end = ft_strchr(str, '\0') - 1;

	while (str_end > str)
		ft_swapbyte(str++, str_end--);
}

int	reversed_strcmp(const char *str1, const char *str2)
{
	char	*rev_str1 = ft_strdup(str1);
	char	*rev_str2 = ft_strdup(str2);

	ft_strreverse(rev_str1);
	ft_strreverse(rev_str2);
	// SHOW(rev_str1);
	// SHOW(rev_str2);
	const int	ret = ft_strcmp(rev_str1, rev_str2);
	free(rev_str1);
	free(rev_str2);
	return (ret);
}


int str_suffix_diff(const char* str1, const char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int i = len1 - 1, j = len2 - 1;

	if (len2 == 0)
		return (0);
    while (i >= 0 && j > 0 && str1[i] == str2[j]) {
        i--;
        j--;
    }

    return str1[i] - str2[j];
}

void	test(const char *str, const char *suffix)
{
	ft_dprintf(2, "str      : [%s]\n", str);
	ft_dprintf(2, "suffix   : [%s]\n", suffix);
	// ft_dprintf(2, "chat_diff: %d\n", str_suffix_diff(str, suffix));
	ft_dprintf(2, "my_diff  : %d\n", cmp_strsuffix(str, suffix));
	// ft_dprintf(2, "reversed : %d\n", reversed_strcmp(str, suffix));
	// ft_dprintf(2, "recmp    : %d\n", restrcmp(str, suffix));
	ft_dprintf(2, "\n");
}

int	main(void)
{

	test("Hatsune Miku is cute", "cute");
	test("Hatsune Miku is cute", "ute");
	test("Hatsune Miku is cute", "te");
	test("Hatsune Miku is cute", "e");
	test("Hatsune Miku is cute", "");
	test("Hatsune Miku is cute", "Hatsune Miku is cute");
	test("", "");

	test(".", ".");
	test(".", "");
	test("", ".");
	test(&"."[1], ".");
	test("Hatsune Miku is cute", "s");
	test("Hatsune Miku is cute", "H");

	test("", "Hatsune Miku is cute");
	test("e", "Hatsune Miku is cute");
	test("s", "Hatsune Miku is cute");
	test("H", "Hatsune Miku is cute");
}
