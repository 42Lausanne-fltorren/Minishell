/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:28:44 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/11 11:14:46 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	uint8_t	*b;
	uint8_t	*l;
	size_t	i;
	size_t	j;

	i = 0;
	b = (uint8_t *) big;
	l = (uint8_t *) little;
	if (*l == '\0' || l == NULL)
		return ((char *) big);
	if (len == 0)
		return (NULL);
	while (b[i] && i < len)
	{
		j = 0;
		while (b[i + j] == l[j] && i + j < len)
		{
			if (l[j + 1] == '\0')
				return (&((char *) b)[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
