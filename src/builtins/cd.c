/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:32:41 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 23:27:13 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_cd(t_token **args, char **envp, int fd)
{

	(void) fd;
	if (args && args[1])
	{
		ft_printf("cd: too many arguments\n");
		return (1);
	}
	else if (!args || !args[0])
	{
		if (chdir(ft_getenv("$HOME", envp)) == -1)
		{
			ft_printf("cd: HOME not set\n");
			perror("minishell");
			return (1);
		}
	}
	else if (chdir(args[0]->value) == -1)
	{
		ft_printf("cd: %s: %s\n", args[0]->value, strerror(errno));
		return (1);
	}
	return (0);
}
