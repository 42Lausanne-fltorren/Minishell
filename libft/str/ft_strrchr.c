/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:37:32 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/11 11:16:16 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*last;
	size_t	i;
	size_t	len;

	len = ft_strlen(str);
	i = 0;
	last = NULL;
	while (i < (len + 1))
	{
		if (str[i] == (char) c)
			last = (&((char *) str)[i]);
		i++;
	}
	return (last);
}
