/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:33:31 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 23:55:11 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	thread(t_command cmd, char **envp)
{
	if (cmd.cmd->value == NULL)
		exit(1);
	execve(cmd.cmd->value, ft_get_args(cmd), envp);
	perror("execve");
	exit(1);
}

void	ft_free_all(int **pipes, pid_t *pids, int cmd_count)
{
	int	i;

	i = -1;
	while (++i < cmd_count)
		free(pipes[i]);
	free(pipes);
	free(pids);
}

static int	execute_builtin(int **pipes, t_command *cmds, int i, char **envp)
{
	int	status;

	close(pipes[i - 1][0]);
	status = cmds[i - 1].builtin(cmds[i - 1].args, envp, pipes[i - 1][1]);
	close(pipes[i - 1][1]);
	return (status);
}

int	execute(int **pipes, pid_t *pids, t_command *cmds, char **envp)
{
	int	i;
	int	status;

	i = -1;
	while (++i < ft_commands_len(cmds))
	{
		pids[i] = -1;
		if (cmds[i].builtin && ((i + 1 < ft_commands_len(cmds)
					&& cmds[i + 1].builtin) || i == ft_commands_len(cmds) - 1))
			status = cmds[i].builtin(cmds[i].args, envp, STDOUT_FILENO);
		if (!cmds[i].builtin)
		{
			pids[i] = fork();
			if (pids[i] == 0)
			{
				ft_setup_io(pipes, i, ft_commands_len(cmds), cmds[i]);
				thread(cmds[i], envp);
			}
			else if (pids[i] < 0)
				perror("fork");
			else if (i - 1 >= 0 && cmds[i - 1].builtin)
				status = execute_builtin(pipes, cmds, i, envp);
		}
	}
	return (status);
}

int	executor(t_command *commands, char **envp)
{
	pid_t	*pids;
	int		cmd_count;
	int		**pipes;
	int		status;

	cmd_count = ft_commands_len(commands);
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (1);
	pipes = ft_init_pipes(cmd_count, pids);
	if (!pipes)
		return (1);
	status = execute(pipes, pids, commands, envp);
	ft_close(pipes, cmd_count);
	ft_wait(cmd_count, pids, &status);
	ft_free_all(pipes, pids, cmd_count);
	return (status);
}
