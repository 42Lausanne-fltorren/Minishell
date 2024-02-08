/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:13:40 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/09 11:14:15 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *area, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) area;
	while (n--)
		*ptr++ = (unsigned char) c;
	return (area);
}
