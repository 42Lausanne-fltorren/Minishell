/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:15:36 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/09 15:23:35 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t len)
{
	uint8_t	*s;
	size_t	n;

	s = (uint8_t *) src;
	n = -1;
	while (++n < len)
	{
		if (s[n] == (uint8_t) c)
			return (&s[n]);
	}
	return (NULL);
}
