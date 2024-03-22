/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:43:19 by fltorren          #+#    #+#             */
/*   Updated: 2024/03/17 19:18:03 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_wait(int cmd_count, pid_t *pids, int *status)
{
	int	i;

	i = -1;
	while (++i < cmd_count)
		waitpid(pids[i], &status[i], 0);
}

int	ft_commands_len(t_command *commands)
{
	int	i;

	i = 0;
	while (commands[i].cmd)
		i++;
	return (i);
}

int	ft_command_args_len(t_command command)
{
	int	i;

	if (!command.args)
		return (0);
	i = 0;
	while (command.args[i])
		i++;
	return (i);
}

char	**ft_get_args(t_command command)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (ft_command_args_len(command) + 2));
	if (!args)
		return (NULL);
	args[0] = command.cmd->value;
	i = 0;
	while (command.args && command.args[i])
	{
		args[i + 1] = command.args[i]->value;
		i++;
	}
	args[i + 1] = NULL;
	return (args);
}
