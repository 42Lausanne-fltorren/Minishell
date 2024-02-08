/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:05:18 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/07 17:21:15 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_get_width(va_list args, const char *format, int i, t_flags *flags)
{
	int	j;

	j = 0;
	if (format[i + j] == '*')
	{
		flags->width = va_arg(args, int);
		j++;
	}
	else if (format[i + j] >= '0' && format[i + j] <= '9')
	{
		flags->width = ft_atoi(&format[i + j]);
		j += ft_get_digits(flags->width, 10);
	}
	return (j);
}

int	is_flag(char c)
{
	if (c == '-' || c == '0' || c == '.' || c == '*'
		|| (c >= '0' && c <= '9') || c == ' ' || c == '#' || c == '+')
		return (1);
	return (0);
}

void	ft_get_flag(const char c, t_flags *flags)
{
	if (c == '-')
		flags->minus = 1;
	else if (c == '0')
		flags->zero = 1;
	else if (c == '.')
		flags->dot = 1;
	else if (c == ' ')
		flags->space = 1;
	else if (c == '#')
		flags->alt = 1;
	else if (c == '+')
		flags->plus = 1;
}

int	ft_get_flags(va_list args, const char *format, int i, t_flags *flags)
{
	int	j;

	*flags = (t_flags){0, 0, 0, 0, 0, 0, 0, 0};
	j = 0;
	while (is_flag(format[i + j]))
	{
		if (format[i + j] == '-' || format[i + j] == '0'
			|| format[i + j] == '.' || format[i + j] == '*'
			|| format[i + j] == ' ' || format[i + j] == '#'
			|| format[i + j] == '+')
		{
			ft_get_flag(format[i + j], flags);
			j++;
		}
		if (flags->dot && flags->precision == 0 && format[i + j] != '0')
			j += ft_get_precision(args, format, i + j, flags);
		else if (flags->width == 0 && format[i + j] != '0')
			j += ft_get_width(args, format, i + j, flags);
	}
	return (j);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	size_t	i;
	size_t	len;
	t_flags	flags;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			i += ft_get_flags(args, format, i, &flags);
			len += ft_put_type(args, format, i, flags);
		}
		else
		{
			write(1, &format[i], 1);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}

// #include <stdio.h>
// #include <limits.h>
// int	main(void)
// {
// 	int len;
// 	int rlen;

// 	len = ft_printf(".% 2d.\n", 0);
// 	rlen = printf(".% 2d.\n", 0);
// 	printf("len = %d, rlen = %d\n", len, rlen);
// 	// len = ft_printf("%5.c\n", 'c');
// 	// rlen = printf("%5.c\n", 'c');
// 	// printf("len = %d, rlen = %d\n", len, rlen);
// 	return (0);
// }