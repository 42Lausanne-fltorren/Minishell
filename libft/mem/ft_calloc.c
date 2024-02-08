/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 22:27:15 by fltorren          #+#    #+#             */
/*   Updated: 2023/10/09 22:34:47 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned long	mult;
	void			*mem;

	mult = nmemb * size;
	if (mult > UINT32_MAX)
		return (NULL);
	mem = (void *) malloc(mult);
	if (mem)
		ft_bzero(mem, mult);
	return (mem);
}
