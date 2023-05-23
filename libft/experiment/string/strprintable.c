#include "libft.h"

static void	print(char c)
{
	write(1, &c, 1);
}

static void	print_hex(unsigned int nbr)
{
	if (nbr < 10)
		print(nbr + '0');
	else
		print(nbr - 10 + 'a');
}

void	ft_putstr_non_printable(const char *str)
{
	str--;
	while (*++str)
		if (ft_isprint(*str))
			print(*str);
	else
	{
		print('\\');
		print_hex(*str / 16);
		print_hex(*str % 16);
	}
	// else
	// 	ft_printf("\\%02x", *str);
}

static void	ft_printno(const char *src, const char *base)
{
	char	*print;

	print = ft_strprintable(src, base);
	ft_printf("%s\n", print);
	free(print);
}

static void	ft_printno_sign(const char *src)
{
	char	*print;

	print = ft_strprintable_sign(src);
	ft_printf("%s\n", print);
	free(print);
}

static void	allbase(const char *src)
{
	ft_printf("src: %s\n", src);
	ft_printf("\nBinary\n");
	ft_printno(src, "01");
	ft_printf("\nOctal\n");
	ft_printno(src, "01234567");
	ft_printf("\nDecimal\n");
	ft_printno(src, "0123456789");
	ft_printf("\nHexadecimal\n");
	ft_printno(src, "0123456789abcdef");
}

static void	putno(const char *str)
{
	ft_putstr_non_printable(str);
	ft_printf("\n");
}

	// putno("Coucou\ntu vas bien ?\n");
	// putno("Hatsune \t Miku \t is   very \t cute \n");
int	main(void)
{
	int	nbr;

	nbr = 0xffffff;
	allbase("Coucou\ntu vas bien ?\n");
	allbase("Hatsune \t Miku \t is   very \t cute \n");
	allbase("Hatsune Miku\200");
	allbase("初音未來,  人類的未來");
	allbase((char *)&nbr);
}
	// ft_printno_sign("Coucou\ntu vas bien ?\n");
	// ft_printno_sign("Hatsune \t Miku \t is   very \t cute \n");

static void	memprintable(const void *src, const char *base, size_t bytes)
{
	char	*str_printable;

	str_printable = ft_memprintable(src, base, bytes);
	ft_printf("base(%d): %s\n", ft_strlen(base), base);
	ft_printf("%s\n", str_printable);
	free(str_printable);
}

static void	testnbr_memprintable(unsigned int nbr)
{
	ft_printf("nbr: %x\n", nbr);
	ft_printf("\nBinary\n");
	memprintable(&nbr, "01", sizeof(nbr));
	ft_printf("\nOctal\n");
	memprintable(&nbr, "01234567", sizeof(nbr));
	ft_printf("\nDecimal\n");
	memprintable(&nbr, "0123456789", sizeof(nbr));
	ft_printf("\nHexadecimal\n");
	memprintable(&nbr, "0123456789abcdef", sizeof(nbr));
}

static void	test_memprintable(const void *src, size_t bytes)
{
	ft_printf("\nBinary\n");
	memprintable(src, "01", bytes);
	ft_printf("\nOctal\n");
	memprintable(src, "01234567", bytes);
	ft_printf("\nDecimal\n");
	memprintable(src, "0123456789", bytes);
	ft_printf("\nHexadecimal\n");
	memprintable(src, "0123456789abcdef", bytes);
}

// int	main(void)
// {
// 	testnbr_memprintable(0x0);
// 	testnbr_memprintable(0xffffff);
// 	test_memprintable("初音未來,  人類的未來", ft_strlen("初音未來,  人類的未來"));
// 	(void)testnbr_memprintable;
// 	(void)test_memprintable;
// }
