/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:33:31 by fltorren          #+#    #+#             */
/*   Updated: 2024/03/15 14:46:45 by fltorren         ###   ########.fr       */
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
			dup2(open(cmd.out->value, O_WRONLY | O_CREAT | O_TRUNC, 0644),
				STDOUT_FILENO);
		else if (cmd.append)
			dup2(open(cmd.append->value, O_WRONLY | O_CREAT | O_APPEND, 0644),
				STDOUT_FILENO);
	}
	else
		dup2(pipe_fd[1], STDOUT_FILENO);
}

void	thread(t_command cmd, char **envp)
{
	execve(cmd.cmd->value, ft_get_args(cmd), envp);
	exit(1);
}

static int	ft_wait(pid_t *pids, int cmd_count, int *pipe_fd)
{
	int	status;
	int	i;

	i = -1;
	while (++i < cmd_count)
	{
		if (i < cmd_count - 1)
			close(pipe_fd[1]);
		if (i > 0)
			close(pipe_fd[0]);
		waitpid(pids[i], &status, 0);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	executor(t_command *commands, char **envp)
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
			thread(commands[i], envp);
		}
	}
	ft_wait(pids, cmd_count, pipe_fd);
	free(pids);
	return (0);
}

// int executor(t_command *commands)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		printf("Executing: %s\n", commands[0].cmd->value);
// 		char **args = ft_get_args(commands[0]);
// 		int i = 0;
// 		while (args[i])
// 		{
// 			printf("args[%d]: %s\n", i, args[i]);
// 			i++;
// 		}
// 		execve(commands[0].cmd->value, args, NULL);
// 		exit(1);
// 	}
// 	else
// 	{
// 		int status;
// 		waitpid(pid, &status, 0);
// 		printf("Child exited with status %d\n", WEXITSTATUS(status));
// 		if (WIFEXITED(status))
// 			return (WEXITSTATUS(status));
// 	}
// 	return 0;
// }
