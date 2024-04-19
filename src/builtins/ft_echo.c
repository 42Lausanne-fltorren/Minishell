/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:32:41 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 23:47:50 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_echo(t_token **args, char **envp, int fd)
{
	int	i;
	int	n;

	(void)envp;
	if (!args || !args[0])
	{
		ft_putstr_fd("\n", fd);
		return (0);
	}
	n = args[0] && !ft_strncmp(args[0]->value, "-n", 2);
	i = n;
	while (args[i])
	{
		ft_putstr_fd(args[i]->value, fd);
		i++;
		if (args[i])
			ft_putstr_fd(" ", fd);
	}
	if (!n)
		ft_putstr_fd("\n", fd);
	return (0);
}
