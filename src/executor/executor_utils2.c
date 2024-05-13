/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:43:19 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 14:33:37 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_command cmd, char ***envp, int fd)
{
	if (cmd.open_error != NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd.open_error);
		return (1);
	}
	if (cmd.out)
	{
		fd = open(cmd.out->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(cmd.out->value);
			return (1);
		}
	}
	return (cmd.builtin(cmd.args, envp, fd));
}
