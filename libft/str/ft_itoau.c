/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoau.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:01:30 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/07 17:03:12 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_get_digits(unsigned long n, int base)
{
	size_t	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n)
	{
		i++;
		n /= base;
	}
	return (i);
}

char	*ft_itoau(unsigned int n)
{
	char	*str;
	size_t	i;

	str = (char *) ft_calloc(ft_get_digits(n, 10) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = ft_get_digits(n, 10);
	while (i > 0)
	{
		str[--i] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
