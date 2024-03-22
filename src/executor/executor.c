/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:33:31 by fltorren          #+#    #+#             */
/*   Updated: 2024/03/17 19:51:20 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	thread(t_command cmd, char **envp)
{
	if (cmd.builtin)
	{
		cmd.builtin(cmd.args);
		exit(0);
	}
	else
	{
		execve(cmd.cmd->value, ft_get_args(cmd), envp);
		exit(1);
	}
}

static void	ft_free_all(int **pipes, pid_t *pids, int cmd_count)
{
	int	i;

	i = -1;
	while (++i < cmd_count)
		free(pipes[i]);
	free(pipes);
	free(pids);
}

int	**ft_init_pipes(int cmd_count, pid_t *pids)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * cmd_count);
	if (!pipes)
		return (NULL);
	i = -1;
	while (++i < cmd_count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			ft_free_all(pipes, pids, i);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			ft_free_all(pipes, pids, i);
			return (NULL);
		}
	}
	return (pipes);
}

void	execute(int **pipes, pid_t *pids, t_command *commands, char **envp)
{
	int	i;
	int	cmd_count;

	cmd_count = ft_commands_len(commands);
	i = -1;
	while (++i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			ft_setup_io(pipes, i, cmd_count, commands[i]);
			thread(commands[i], envp);
		}
		else if (pids[i] == -1)
		{
			perror("fork");
			exit(1);
		}
	}
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
	execute(pipes, pids, commands, envp);
	ft_close(pipes, cmd_count);
	ft_wait(cmd_count, pids, &status);
	ft_free_all(pipes, pids, cmd_count);
	return (status);
}
