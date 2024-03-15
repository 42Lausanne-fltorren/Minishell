/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:32:41 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/20 14:37:26 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_echo(t_command cmd)
{
	int	i;
	int	n;

	//check if first argument is -n
	n = cmd.args[0] && !ft_strncmp(cmd.args[0]->value, "-n", 2);
	i = n;
	while (cmd.args[i])
	{
		ft_printf("%s", cmd.args[i]->value);
		i++;
		if (cmd.args[i])
			ft_printf(" ");
	}
	if (!n)
		ft_printf("\n");
	return (0);
}
