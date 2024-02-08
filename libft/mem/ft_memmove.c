/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:44:07 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/09 15:13:42 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	uint8_t	*from;
	uint8_t	*to;
	int		i;

	from = (uint8_t *) src;
	to = (uint8_t *) dest;
	if (from == to || n == 0)
		return (dest);
	if (to > from && to - from < (int) n)
	{
		i = n;
		while (--i >= 0)
			to[i] = from[i];
		return (dest);
	}
	if (from > to && from - to < (int) n)
	{
		i = -1;
		while (++i < (int) n)
			to[i] = from[i];
		return (dest);
	}
	ft_memcpy(dest, src, n);
	return (dest);
}
