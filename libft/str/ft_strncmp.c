/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 21:23:48 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/09 21:27:44 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	int		c;
	uint8_t	*s1;
	uint8_t	*s2;

	s1 = (uint8_t *) str1;
	s2 = (uint8_t *) str2;
	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0') && i < n)
	{
		c = s1[i] - s2[i];
		if (c != 0)
			return (c);
		i++;
	}
	return (0);
}
