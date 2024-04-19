/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:32:41 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 23:27:11 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_echo(t_token **args, char **envp, int fd)
{
	int	i;
	int	n;

	(void)envp;
	(void)fd;
	if (!args || !args[0])
	{
		ft_printf("\n");
		return (0);
	}
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
