/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:02:44 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/07 17:12:26 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(unsigned long n, char *base)
{
	char	*str;
	size_t	i;
	size_t	base_len;

	base_len = ft_strlen(base);
	str = (char *) ft_calloc(ft_get_digits(n, base_len) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = ft_get_digits(n, base_len);
	while (i > 0)
	{
		str[--i] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}
