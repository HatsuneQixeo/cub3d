#include "libft.h"

int	ft_prompt_nbr(const char *request)
{
	char	*input;
	int		nbr;

	input = ft_prompt(request);
	nbr = ft_atoi(input);
	free(input);
	return (nbr);
}

void	ft_bitprint(unsigned int nbr)
{
	char	*str;

	str = ft_utoa_base(nbr, "01");
	str = ft_strcombine(ft_strcreate('0', (sizeof(nbr) * 8) - ft_strlen(str)), str);
	ft_printf("bit(%d): %s\n", nbr, str);
	free(str);
}

void	ft_show(int nbr, int shift)
{

}

void	bits_print(int nbr)
{
	ft_printf("Bits:\n");
	ft_bitprint(nbr);
	ft_memprint(&nbr, sizeof(int), sizeof(int));
	ft_printf("End\n");
}

int	main(void)
{
	int		nbr;
	int		shift;
	int		shifted_nbr;

	while (1)
	{
		nbr = ft_prompt_nbr("Enter number");
		shift = ft_prompt_nbr("Enter amount of bits to be shifted");
		ft_printf("%d : %d\n", nbr, shift);
		bits_print(nbr);
		shifted_nbr = nbr << shift;
		ft_printf("%d << %d = %d\n", nbr, shift, shifted_nbr);
		bits_print(shifted_nbr);
		shifted_nbr = nbr >> shift;
		ft_printf("%d >> %d = %d\n", nbr, shift, shifted_nbr);
		bits_print(shifted_nbr);
	}
}
