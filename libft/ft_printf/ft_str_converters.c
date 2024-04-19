/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_converters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:06:17 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/18 23:24:11 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_char(va_list args, t_flags flags)
{
	char	c;

	c = va_arg(args, int);
	if (flags.minus == 1)
	{
		write(STDOUT_FILENO, &c, 1);
		ft_put_width(flags.width, 1);
	}
	else
	{
		ft_put_width(flags.width, 1);
		write(STDOUT_FILENO, &c, 1);
	}
	return (ft_max(flags.width, 1));
}

int	ft_put_str(va_list args, t_flags flags)
{
	char	*str;
	int		len;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (flags.dot)
		len = ft_min(len, flags.precision);
	if (flags.minus == 1)
	{
		write(STDOUT_FILENO, str, len);
		ft_put_width(flags.width, len);
	}
	else
	{
		ft_put_width(flags.width, len);
		write(STDOUT_FILENO, str, len);
	}
	return (ft_max(flags.width, len));
}

int	ft_put_perc(t_flags flags)
{
	if (flags.minus == 1)
	{
		write(STDOUT_FILENO, "%", 1);
		ft_put_width(flags.width, 1);
	}
	else if (flags.zero == 1)
	{
		ft_put_zeroes(flags.width, 1);
		write(STDOUT_FILENO, "%", 1);
	}
	else
	{
		ft_put_width(flags.width, 1);
		write(STDOUT_FILENO, "%", 1);
	}
	return (ft_max(flags.width, 1));
}
