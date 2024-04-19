/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:32:41 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 23:46:43 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_cd(t_token **args, char **envp, int fd)
{
	(void) fd;
	if (args && args[1])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	else if (!args || !args[0])
	{
		if (chdir(ft_getenv("$HOME", envp)) == -1)
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (chdir(args[0]->value) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(args[0]->value, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}
