/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:32:41 by fltorren          #+#    #+#             */
/*   Updated: 2024/03/17 19:52:19 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_echo(t_token **args)
{
	int	i;
	int	n;

	n = args[0] && !ft_strncmp(args[0]->value, "-n", 2);
	i = n;
	while (args[i])
	{
		ft_printf("%s", args[i]->value);
		i++;
		if (args[i])
			ft_printf(" ");
	}
	if (!n)
		ft_printf("\n");
	return (0);
}
