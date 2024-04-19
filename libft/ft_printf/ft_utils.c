/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:07:09 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/18 23:24:25 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strtoupper(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

void	ft_put_width(int width, int len)
{
	while (width > len)
	{
		write(STDOUT_FILENO, " ", 1);
		width--;
	}
}

void	ft_put_zeroes(int width, int len)
{
	while (width > len)
	{
		write(STDOUT_FILENO, "0", 1);
		width--;
	}
}

int	ft_put_type(va_list args, const char *format, int i, t_flags flags)
{
	if (format[i] == 'c')
		return (ft_put_char(args, flags));
	else if (format[i] == 's')
		return (ft_put_str(args, flags));
	else if (format[i] == 'd' || format[i] == 'i')
		return (ft_put_int(args, flags));
	else if (format[i] == 'u')
		return (ft_put_uint(args, flags));
	else if (format[i] == 'x' || format[i] == 'X')
		return (ft_put_hex(args, format[i], flags));
	else if (format[i] == 'p')
		return (ft_put_ptr(args, flags));
	else if (format[i] == '%')
		return (ft_put_perc(flags));
	return (0);
}

int	ft_get_precision(va_list args, const char *format, int i, t_flags *flags)
{
	int	j;

	j = 0;
	if (format[i + j] == '*')
	{
		flags->precision = va_arg(args, int);
		j++;
	}
	else if (format[i + j] >= '0' && format[i + j] <= '9')
	{
		flags->precision = ft_atoi(&format[i + j]);
		j += ft_get_digits(flags->precision, 10);
	}
	return (j);
}
