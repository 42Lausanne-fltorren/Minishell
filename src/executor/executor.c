/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:33:31 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 23:27:47 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	thread(t_command cmd, char **envp)
{
	execve(cmd.cmd->value, ft_get_args(cmd), envp);
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

void	execute(int **pipes, pid_t *pids, t_command *commands, char **envp)
{
	// int	i;
	// int	cmd_count;

	// (void) pipes;
	// cmd_count = ft_commands_len(commands);
	// i = -1;
	// while (++i < cmd_count)
	// {
	// 	pids[i] = -1;
	// 	if (commands[i].builtin && ((i + 1 < cmd_count
	// 				&& commands[i + 1].builtin) || i == cmd_count - 1))
	// 		commands[i].builtin(commands[i].args, envp);
	// 	if (!commands[i].builtin)
	// 	{
	// 		pids[i] = fork();
	// 		if (pids[i] == 0)
	// 		{
	// 			// ft_setup_io(pipes, i, cmd_count, commands[i]);
	// 			dup2(pipes[i][0], STDIN_FILENO);
	// 			close(pipes[i + 1][0]);
	// 			close(pipes[i + 1][1]);
	// 			close(pipes[i][1]);
	// 			execve(commands[i].cmd->value, ft_get_args(commands[i]), envp);
	// 		}
	// 		else if (pids[i] == -1)
	// 			perror("fork");
	// 		else if (i - 1 > 0 && commands[i - 1].builtin)
	// 		{
	// 			close(pipes[i][1]);
	// 			close(pipes[i][0]);
	// 			close(pipes[i - 1][0]);
	// 			commands[i - 1].builtin(commands[i - 1].args, envp);
	// 			close(pipes[i - 1][1]);
	// 			// ft_close(pipes, cmd_count);
	// 		}
	// 	}
	// }

	int	i;
	int	cmd_count;

	cmd_count = ft_commands_len(commands);
	i = -1;
	while (++i < cmd_count)
	{
		pids[i] = -1;
		if (commands[i].builtin && ((i + 1 < cmd_count
					&& commands[i + 1].builtin) || i == cmd_count - 1))
			commands[i].builtin(commands[i].args, envp, STDOUT_FILENO);
		if (!commands[i].builtin)
		{
			pids[i] = fork();
			if (pids[i] == 0)
			{
				close(pipes[i - 1][1]);
				dup2(pipes[i - 1][0], STDIN_FILENO);
				// ft_setup_io(pipes, i, cmd_count, commands[i]);
				execve(commands[i].cmd->value, ft_get_args(commands[i]), envp);
				perror("execve");
				exit(1);
			}
			else if (pids[i] < 0)
			{
				perror("fork");
				exit(1);
			}
			else if (i - 1 >= 0 && commands[i - 1].builtin)
			{
				close(pipes[i - 1][0]);
				commands[i - 1].builtin(commands[i - 1].args, envp, pipes[i - 1][1]);
				close(pipes[i - 1][1]);
				write(1, "\0", 1);
				waitpid(pids[i], NULL, 0);
			}
		}
	}
}

void	execute_builtins(t_command *commands, int **pipes, char **envp)
{
	int	i;
	int	cmd_count;

	cmd_count = ft_commands_len(commands);
	i = -1;
	while (++i < cmd_count)
	{
		if (!commands[i].builtin)
			continue ;
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][0]);
		commands[i].builtin(commands[i].args, envp, STDOUT_FILENO);
		close(pipes[i][1]);
	}
}

int	executor(t_command *commands, char **envp)
{
	pid_t	*pids;
	int		cmd_count;
	int		**pipes;
	// int		status;

	cmd_count = ft_commands_len(commands);
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (1);
	pipes = ft_init_pipes(cmd_count, pids);
	if (!pipes)
		return (1);
	execute(pipes, pids, commands, envp);
	// ft_close(pipes, cmd_count);
	// ft_wait(cmd_count, pids, &status);
	ft_free_all(pipes, pids, cmd_count);
	return (0);
}
