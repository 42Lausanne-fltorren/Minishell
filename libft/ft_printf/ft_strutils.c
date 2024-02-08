/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:06:43 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/07 17:15:18 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_reassign(char **str, char *new)
{
	free(*str);
	*str = new;
}

char	*ft_join_zeroes(char *str, int n)
{
	char	*tmp;
	int		i;

	tmp = malloc(sizeof(char) * (ft_strlen(str) + n + 1));
	i = 0;
	while (i < n)
		tmp[i++] = '0';
	tmp[i] = '\0';
	return (ft_strjoin(tmp, str));
}

char	*ft_join_spaces(char *str, int n)
{
	char	*tmp;
	int		i;

	tmp = malloc(sizeof(char) * (ft_strlen(str) + n + 1));
	i = 0;
	while (i < n)
		tmp[i++] = ' ';
	tmp[i] = '\0';
	return (ft_strjoin(tmp, str));
}
