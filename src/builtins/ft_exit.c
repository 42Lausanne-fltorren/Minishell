/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:50:53 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 23:51:40 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_exit(t_token **args, char **envp, int fd)
{
	int	i;

	(void)envp;
	(void)fd;
	if (!args || !args[0])
		exit(0);
	if (args[1])
	{
		ft_putstr_fd("exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	i = -1;
	while (args[0]->value[++i])
	{
		if (!ft_isdigit(args[0]->value[i]) && args[0]->value[i] != '-'
			&& args[0]->value[i] != '+')
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(args[0]->value, STDERR_FILENO);
			ft_putstr_fd(": numeric argument required", STDERR_FILENO);
			exit(2);
		}
	}
	exit(ft_atoi(args[0]->value));
}
