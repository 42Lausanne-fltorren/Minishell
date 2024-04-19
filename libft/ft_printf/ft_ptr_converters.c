/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_converters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:05:45 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/18 23:24:14 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	put(char *str, int len, t_flags flags)
{
	if (flags.minus == 1)
	{
		write(STDOUT_FILENO, "0x", 2);
		write(STDOUT_FILENO, str, len);
		ft_put_width(flags.width, len + 2);
	}
	else if (flags.zero == 1)
	{
		write(STDOUT_FILENO, "0x", 2);
		ft_put_zeroes(flags.width, len);
		write(STDOUT_FILENO, str, len);
	}
	else
	{
		ft_put_width(flags.width, len + 2);
		write(STDOUT_FILENO, "0x", 2);
		write(STDOUT_FILENO, str, len);
	}
	free(str);
}

int	ft_put_ptr(va_list args, t_flags flags)
{
	uintptr_t	n;
	void		*ptr;
	char		*str;
	int			len;

	ptr = va_arg(args, void *);
	n = (uintptr_t) ptr;
	str = ft_itoa_base(n, "0123456789abcdef");
	if (!str)
		return (-1);
	len = ft_strlen(str);
	put(str, len, flags);
	if (flags.zero == 1)
		return (ft_max(flags.width + 2, len + 2));
	return (ft_max(flags.width, len + 2));
}
