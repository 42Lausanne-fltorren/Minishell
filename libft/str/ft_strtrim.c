/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:29:51 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/10 14:02:13 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isinset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	len;
	size_t	i;
	char	*trim;

	if (!str || !set)
		return (NULL);
	i = 0;
	while (isinset(str[i], set))
		i++;
	len = 0;
	while (str[i + len])
		len++;
	while (isinset(str[i + len - 1], set) && len > 0)
		len--;
	trim = (char *) ft_calloc(len + 1, 1);
	if (!trim)
		return (NULL);
	ft_strlcpy(trim, (str + i), len + 1);
	return (trim);
}
