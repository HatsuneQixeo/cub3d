/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hqixeo <hqixeo@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 01:03:19 by hqixeo            #+#    #+#             */
/*   Updated: 2023/05/20 17:53:52 by hqixeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include "libto.h"

# define BINARY			"01"
# define OCTAL			"01234567"
# define DECIMAL		"0123456789"
# define HEXADECIMAL	"0123456789abcdef"
# define UPPERHEX		"0123456789ABCDEF"

typedef struct flags
{
	char	format;
	char	plus;
	char	space;
	char	sharp;
	char	mod_long;
	char	mod_short;
	char	mod_z;
	char	negative_field;
	char	zero;
	char	period;
	int		width;
	int		precision;
}			t_flags;

/* Put */
void	ft_memprint(const void *ptr, size_t bytes, size_t data_size);
int		ft_putchar_fd(char c, int fd);
int		ft_putendl_fd(const char *str, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(const char *str, int fd);
int		ft_strrelease_fd(char *str, int fd);

int		ft_printf_core(int fd, const char *str, va_list args);
int		ft_printf(const char *str, ...);
int		ft_dprintf(int fd, const char *str, ...);

char	*ft_flagextract(const char *str, t_flags *flags, va_list args);
char	*ft_decimal(long long d, const t_flags *flags);
char	*ft_unsigned(unsigned long long hex, const t_flags *flags);
int		ft_conversion(int fd, va_list args, const t_flags *flags);
char	*ft_strfinalize(char *str, const t_flags *flags);

#endif
