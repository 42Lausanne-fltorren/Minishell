/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:33:31 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/16 16:08:08 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_setup_io(t_command cmd, int *pipe_fd, int i, int len)
{
	if (i == 0)
	{
		if (cmd.in)
			dup2(open(cmd.in->value, O_RDONLY), STDIN_FILENO);
	}
	else
		dup2(pipe_fd[0], STDIN_FILENO);
	if (i == len - 1)
	{
		if (cmd.out)
			dup2(open(cmd.out->value, O_WRONLY | O_CREAT | O_TRUNC, 0644), STDOUT_FILENO);
		else if (cmd.append)
			dup2(open(cmd.append->value, O_WRONLY | O_CREAT | O_APPEND, 0644), STDOUT_FILENO);
	}
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	thread(t_command cmd)
{
	execve(cmd.cmd->value, ft_get_args(cmd), NULL);
	exit(1);
}

int	executor(t_command *commands)
{
	int		pipe_fd[2];
	pid_t	*pids;
	int		cmd_count;
	int		i;

	cmd_count = ft_commands_len(commands);
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (1);
	i = -1;
	while (++i < cmd_count)
	{
		if (i < cmd_count - 1)
			pipe(pipe_fd);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			ft_setup_io(commands[i], pipe_fd, i, cmd_count);
			thread(commands[i]);
		}
		else
		{
			waitpid(pids[i], NULL, 0);
			if (i > 0)
				close(pipe_fd[0]);
			if (i < cmd_count - 1)
				close(pipe_fd[1]);
		}
	}
	free(pids);
	return (0);
}
