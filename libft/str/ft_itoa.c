/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:35:08 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/17 13:45:07 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_digits(int n)
{
	size_t	i;

	i = 0;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return ((unsigned int) -n);
	return ((unsigned int) n);
}

char	*ft_itoa(int n)
{
	size_t		len;
	uint32_t	temp;
	char		*str;

	temp = ft_abs(n);
	len = get_digits(temp);
	if (n == 0)
		len = 1;
	if (n < 0)
		len++;
	str = (char *) ft_calloc(len + 1, 1);
	if (!str)
		return (NULL);
	while (len--)
	{
		str[len] = temp % 10 + '0';
		temp /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
