/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 23:02:32 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/09 23:18:04 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str1, char const *str2)
{
	size_t	len;
	char	*join;

	if (!str1 || !str2)
		return (NULL);
	len = ft_strlen(str1) + ft_strlen(str2) + 1;
	join = (char *) ft_calloc(len, 1);
	if (!join)
		return (NULL);
	ft_strlcat(join, str1, len);
	ft_strlcat(join, str2, len);
	return (join);
}
