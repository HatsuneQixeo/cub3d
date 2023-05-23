#include "libft.h"
#include <limits.h>

/**
 * @brief Float makes literally no sense
 * @remark Consider creating a union for experimental purpose and incrementation
 */
// {
	// int	main(void)
	// {
	// 	printf("1.1:%%f:		%f\n", 1.1);
	// 	printf("1.1:%%.f:	%.f\n", 1.1);
	// 	printf("1.4:%%.f:	%.f\n", 1.4);
	// 	printf("1.5:%%.f:	%.f\n", 1.5);
	// 	printf("1.55:%%.f:	%.f\n", 1.55);
	// 	printf("1.45:%%.f:	%.f\n", 1.45);
	// 	printf("1.5555555:%%.f:	%.f\n", 1.5555555);
	// 	printf("1.13456789:%%.f:	%.f\n", 1.13456789);
	// 	printf("1.1: %%.6f	%.6f\n", 1.1);
	// 	printf("1.1: %%.99f	%.99f\n", 1.1);
	// 	float	i;

	// 	i = 1;
	// 	printf("%.f\n", i);
	// 	// printf("%.10f\n", i += .123456789);
	// 	// printf("%.10f\n", i + .123456789);
	// 	ft_printf("i as d: %d\n", i);
	// 	ft_memprint(&i, 4, 4);
	// 	// while (i += .1)
	// 	// {
	// 	// 	printf("%.10f\n", i);
	// 	// 	ft_printf("i as d: %d\n", i);
	// 	// 	ft_memprint(&i, 4, 4);
	// 	// }
	// }
// }


/**
 * @brief Wildcard width
 * 
 */
// {
	// int	main(void)
	// {
	// 	ft_printf("ft_printf:	(%.*d)\n", 7, 831);
	// 	printf("printf:		(%.*d)\n", 7, 831);
	// 	ft_printf("ft_printf:	(%.*d)\n", -7, 831);
	// 	printf("printf:		(%.*d)\n", -7, 831);
	// 	ft_printf("ft_printf:	(%*d)\n", -7, 831);
	// 	printf("printf:		(%*d)\n", -7, 831);
	// 	ft_printf("ft_printf:	(%*d)\n", 7, 831);
	// 	printf("printf:		(%*d)\n", 7, 831);
	// 	ft_printf("ft_printf:	(%.*s)\n", 7, "Hatsune Miku");
	// 	printf("printf:		(%.*s)\n", 7, "Hatsune Miku");
	// 	ft_printf("ft_printf:	(%.*s)\n", -7, "Hatsune Miku");
	// 	printf("printf:		(%.*s)\n", -7, "Hatsune Miku");
	// 	// printf("(%.*d)\n", 7, 831);
	// 	// printf("(%.*-7d)\n", -7, 831);
	// 	// printf("(%*d)\n", -7, 831);
	// 	// printf("(%.*.4d)\n", -7, -831);
	// // 	printf("(%*d)\n", 7, 831);
	// // 	printf("(%-*d)\n", 7, 831);
	// // 	printf("(%*--d)\n", -7, 831);
	// }
// }

/**
 * @brief Printable conversion as 'b'
 * 
 */
// int	main(void)
// {
// 	ft_printf("%b\n", "Hatsune Miku\n");
// 	ft_printf("%.12b\n", "Hatsune Miku\n");
// 	ft_printf("%.13b\n", "Hatsune Miku\n");
// 	ft_printf("%.13b\n", "Hatsune Miku\n\n");
// 	ft_printf("%.14b\n", "Hatsune Miku\n\n");
// 	ft_printf("%.14b\n", "Hatsune Miku\n\n\n");
// 	system("leaks -q printf_related.miku");
// }

typedef struct print
{
	char	*str;
	size_t	len;
}			t_print;

size_t	ft_lentotal(t_list *lst)
{
	size_t	sum;

	sum = 0;
	while (lst)
	{
		sum += ((t_print *)lst->content)->len;
		lst = lst->next;
	}
	return (sum);
}

void	del_print(void *content)
{
	free(((t_print *)content)->str);
}

int	ft_printall(t_list *lst, int fd)
{
	char	*str_all;
	size_t	len_all;
	t_print	*node_print;

	len_all = ft_lentotal(lst);
	str_all = malloc(len_all);
	while (lst)
	{
		node_print = lst->content;
		ft_memcpy(str_all, node_print->str, node_print->len);
		str_all += node_print->len;
		lst = lst->next;
	}
	write(fd, str_all - len_all, len_all);
	free(str_all);
	ft_lstclear(&lst, del_print);
	return (len_all);
}

/**
 * @brief Long and short modifier priority and invert
 * 
 */
// int	main(void)
// {
// 	// unsigned long	nbr;

// 	// nbr = -1;
// 	ft_printf("lusize: %d\n", sizeof(unsigned long));
// 	ft_printf("llusize: %d\n", sizeof(unsigned long long));
// 	ft_printf("ldsize: %d\n", sizeof(long double));
// 	printf("%hu\n", (unsigned long)-1);
// 	printf("%hhu\n", (unsigned long long)-1);
// 	// if l, else if h
// 	{
// 		// printf("%lu\n", (unsigned long)-1);
// 		// printf("%llu\n", (unsigned long long)-1);
// 		// printf("%lhu\n", (unsigned long)-1);
// 		// printf("%llhu\n", (unsigned long long)-1);
// 		// printf("%hlu\n", (unsigned long)-1);
// 		// printf("%hhlu\n", (unsigned long long)-1);
// 		ft_printf("%lu\n", (unsigned long)-1);
// 		ft_printf("%llu\n", (unsigned long long)-1);
// 		ft_printf("%lhu\n", (unsigned long)-1);
// 		ft_printf("%llhu\n", (unsigned long long)-1);
// 		ft_printf("%hlu\n", (unsigned long)-1);
// 		ft_printf("%hhlu\n", (unsigned long long)-1);
// 	}
// 	//% 2
// 	{	
// 		// printf("%hhhhhhhhu\n", (unsigned long)-1);
// 		// printf("%hhhhhhhhhhhhhu\n", (unsigned long long)-1);
// 		// printf("%hhhhhhhhhhhhhhu\n", (unsigned long long)-1);
// 		// printf("%hhhhhhhhhhhhhhhu\n", (unsigned long long)-1);
// 		ft_printf("%hhhhhhhhd\n", 33333);
// 		ft_printf("%hhhhhhhhhhhhhd\n", 33333);
// 		ft_printf("%hhhhhhhhhhhhhhd\n", 33333);
// 		ft_printf("%hhhhhhhhhhhhhhhd\n", 33333);
// 	}
// 	printf("%zx\n", (size_t)-1);
// }

/**
 * @brief Unsigned long and short
 * 
 */
// int	main(void)
// {
// 	ft_printf("H\n");
// 	printf("%hu\n", -1);
// 	ft_printf("%hu\n", -1);
// 	ft_printf("HH\n");
// 	printf("%hhu\n", -1);
// 	ft_printf("%hhu\n", -1);
// 	ft_printf("HHH\n");
// 	printf("%hhhu\n", -1);
// 	ft_printf("%hhhu\n", -1);
// 	ft_printf("L\n");
// 	printf("%lu\n", (unsigned long)-1);
// 	ft_printf("%lu\n", (unsigned long)-1);
// 	ft_printf("LL\n");
// 	printf("%llu\n", (unsigned long long)-1);
// 	ft_printf("%llu\n", (unsigned long long)-1);
// 	ft_printf("LLL\n");
// 	printf("%lllu\n", (unsigned long)-1);
// 	ft_printf("%lllu\n", (unsigned long)-1);
// }

/**
 * @brief Signed long and short
 * 
 */
// int	main(void)
// {
// 	ft_printf("H\n");
// 	printf("%hd\n", 35000);
// 	ft_printf("%hd\n", 35000);
// 	ft_printf("HH\n");
// 	printf("%hhd\n", 128);
// 	ft_printf("%hhd\n", 128);
// 	ft_printf("HHH\n");
// 	printf("%hhhd\n", -1);
// 	ft_printf("%hhhd\n", -1);
// 	ft_printf("L\n");
// 	printf("%ld\n", -1);
// 	ft_printf("%ld\n", -1);
// 	ft_printf("LL\n");
// 	printf("%lld\n", -1);
// 	ft_printf("%lld\n", -1);
// 	ft_printf("LLL\n");
// 	printf("%llld\n", -1);
// 	ft_printf("%llld\n", -1);
// 	ft_printf("casting\n");
// 	printf("%ld\n", (long)-1);
// 	printf("%lld\n", (long)-1);
// 	printf("%ld\n", -1);
// 	printf("%lld\n", -1);
// 	printf("%lld\n",522337203685470ll);
// 	ft_printf("%lld\n",522337203685470ll);
// 	// for (long number = 0; number > -100; number--)
// 	// 	printf("%ld\n", number);
// }

int notinsubject_o_prec0val0_basic_bench(void){return printf("%.0o", 0);}
int notinsubject_o_prec0val0_implicit_bench(void){return printf("%.o", 0);}
int notinsubject_o_prec0val0_w_bench(void){return printf("%5.0o", 0);}
int notinsubject_o_prec0val0_w_impl_bench(void){return printf("%5.o", 0);}
int notinsubject_o_prec0val0_wlj_bench(void){return printf("%-5.0o", 0);}
int notinsubject_o_prec0val0_wlj_impl_bench(void){return printf("%-5.o", 0);}
int notinsubject_o_prec0val0_af_bench(void){return printf("%#.0o", 0);}
int notinsubject_o_prec0val0_af_impl_bench(void){return printf("%#.o", 0);}
int notinsubject_o_prec0val0_waf_bench(void){return printf("%#5.0o", 0);}
int notinsubject_o_prec0val0_waf_impl_bench(void){return printf("%#5.o", 0);}
int notinsubject_o_prec0val0_waflj_bench(void){return printf("%#-5.0o", 0);}
int notinsubject_o_prec0val0_waflj_impl_bench(void){return printf("%#-5.o", 0);}

/**
 * @brief Octal
 * 
 */
// int	main(void)
// {
// 	printf("\nreturn: %d\n", printf("//%#.0o//", 0));
// 	ft_printf("\nft_return: %d\n", ft_printf("//%#.0o//", 0));
// 	printf("\nreturn: %d\n", printf("//%#.o//", 0));
// 	ft_printf("\nft_return: %d\n", ft_printf("//%#.o//", 0));
// 	printf("\nreturn: %d\n", printf("//%#5.0o//", 0));
// 	ft_printf("\nft_return: %d\n", ft_printf("//%#5.0o//", 0));
// 	printf("\nreturn: %d\n", printf("//%#5.o//", 0));
// 	ft_printf("\nft_return: %d\n", ft_printf("//%#5.o//", 0));
// 	printf("\nreturn: %d\n", printf("//%#-5.0o//", 0));
// 	ft_printf("\nft_return: %d\n", ft_printf("//%#-5.0o//", 0));
// 	printf("\nreturn: %d\n", printf("//%#-5.o//", 0));
// 	ft_printf("\nft_return: %d\n", ft_printf("//%#-5.o//", 0));
// 	printf("\nreturn: %d\n", printf("//%#.0o//", 0));
// 	ft_printf("\nft_return: %d\n", ft_printf("//%#.0o//", 0));
// 	printf("\nreturn: %d\n", printf("printf%02.7o", 3267));
// 	ft_printf("\nft_return: %d\n", ft_printf("ftprintf%02.7o", 3267));
// 	printf("\nreturn: %d\n", printf("(%#0-8.5o)", 0));
// 	ft_printf("\nft_return: %d\n", ft_printf("(%#0-8.5o)", 0));
// }

/**
 * @brief Invalid fd return value
 * Found a bug too
 */
// int	main(void)
// {
// 	printf("%f\n", 0.0);
// 	printf("%8f\n", 0.0);
// 	printf("%.8f\n", 0.0);
// 	printf("%10.1f\n", 0.0);
// 	printf("%f\n", 0.0);
// 	printf("%#f\n", 0.0);
// 	// ft_printf("%d\n", ft_dprintf(1, "Hatsune Miku %s %s\n", "is", "cute"));
// }

char	*ft_ftoa(double n, unsigned int precision)
{
	char			*str;
	char			*decimal;
	unsigned int	i;

	if (n != n)
		return (ft_strdup("nan"));
	else if (n < 0)
		return (ft_strmodify(ft_strrjoin, ft_ftoa(-n, precision), "-"));
	else if (precision == 0)
		return (ft_utoa_base(round(n), DECIMAL));
	str = ft_utoa_base(n, DECIMAL);
	decimal = malloc(sizeof(char) * (precision + 1));
	decimal[precision] = '\0';
	i = -1;
	while (++i < precision)
	{
		n = (n - (long long)n) * 10;
		decimal[i] = (int)n + '0';
	}
	return (ft_strmerge("%f.%f", str, decimal));
}

char	*ft_float(long double n, const t_flags *flags)
{
	char	*str;
	int		precision;

	if (flags->period)
		precision = flags->precision;
	else
		precision = 6;
	str = ft_ftoa(n, precision);
	return (str);
}

int	main(void)
{
	double	n = 1.23456789;
	char	*str;

	str = ft_ftoa(n, 10);
	ft_printf("%s\n", str);
	free(str);
	system("leaks -q printf_related.miku");
}
