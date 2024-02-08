/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_converters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:12:04 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/07 17:12:05 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_put(char *str, t_flags *flags)
{
	char	*tmp;
	int		len;

	tmp = ft_strdup(str);
	if (flags->plus && str[0] != '-')
		ft_reassign(&tmp, ft_strjoin("+", str));
	else if (flags->space && str[0] != '-')
		ft_reassign(&tmp, ft_strjoin(" ", str));
	if (flags->dot && !flags->precision && str[0] == '0')
		ft_reassign(&tmp, ft_strdup(""));
	len = ft_strlen(tmp);
	if (flags->dot && flags->precision > len)
		ft_reassign(&tmp, ft_join_zeroes(str, flags->precision - len));
	len = ft_strlen(tmp);
	if (flags->width > len)
	{
		if (flags->minus || !(flags->zero && !flags->dot))
			ft_reassign(&tmp, ft_join_spaces(tmp, flags->width - len));
		else
			ft_reassign(&tmp, ft_join_zeroes(tmp, flags->width - len));
	}
	ft_putstr_fd(tmp, 1);
	free(tmp);
	return (len);
}

int	ft_put_int(va_list args, t_flags flags)
{
	int		n;
	char	*str;

	n = va_arg(args, int);
	str = ft_itoa(n);
	return (ft_put(str, &flags));
}

int	ft_put_uint(va_list args, t_flags flags)
{
	unsigned int	n;
	char			*str;

	n = va_arg(args, unsigned int);
	str = ft_itoau(n);
	return (ft_put(str, &flags));
}

int	ft_put_hex(va_list args, char type, t_flags flags)
{
	unsigned int	n;
	char			*str;

	n = va_arg(args, unsigned int);
	str = ft_itoa_base(n, "0123456789abcdef");
	if (!str)
		return (-1);
	if (type == 'X')
		ft_strtoupper(str);
	return (ft_put(str, &flags));
}
