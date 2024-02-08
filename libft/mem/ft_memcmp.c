/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:26:19 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/11 09:29:40 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *src1, const void *src2, size_t len)
{
	uint8_t	*s1;
	uint8_t	*s2;
	int		c;
	size_t	i;

	if (len == 0)
		return (0);
	s1 = (uint8_t *) src1;
	s2 = (uint8_t *) src2;
	i = -1;
	while (++i < len)
	{
		c = s1[i] - s2[i];
		if (c != 0)
			return (c);
	}
	return (0);
}
