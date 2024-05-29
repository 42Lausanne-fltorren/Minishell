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

void	thread(t_command *cmds, int i, int **pipes, char **envp)
{
	if (cmds[i].builtin)
		exit(0);
	if (cmds[i].cmd->value == NULL)
		exit(1);
	if (cmds[i].open_error != NULL)
	{
		ft_io_error(cmds[i].open_error);
		exit(1);
	}
	ft_setup_io(pipes, i, ft_commands_len(cmds), cmds[i]);
	if (cmds[i].cmd->value[0] == '\0')
		exit(0);
	if (!ft_isdir(cmds[i].cmd->value) && ft_strlen(cmds[i].cmd->value) > 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmds[i].cmd->value, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		exit(126);
	}
	execve(cmds[i].cmd->value, ft_get_args(cmds[i]), envp);
	ft_putstr_fd("minishell: execve: ", STDERR_FILENO);
	perror(cmds[i].cmd->value);
	exit(126);
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

static int	execute_builtin(int **pipes, t_command *cmds, int i, char ***envp)
{
	int	fd;
	int	status;

	fd = STDOUT_FILENO;
	if (i < ft_commands_len(cmds) - 1)
		fd = pipes[i][1];
	close(pipes[i][0]);
	status = run_builtin(cmds[i], envp, fd);
	close(pipes[i][1]);
	return (status);
}

int	execute(int **pipes, pid_t *pids, t_command *cmds, char ***envp)
{
	int	i;
	int	status;

	i = -1;
	while (++i < ft_commands_len(cmds))
	{
		if (cmds[i].builtin && i == ft_commands_len(cmds) - 1)
		{
			status = execute_builtin(pipes, cmds, i, envp);
			continue ;
		}
		pids[i] = fork();
		if (pids[i] == 0)
			thread(cmds, i, pipes, *envp);
		else if (pids[i] < 0)
			perror("minishell: fork: ");
		if ((i - 1 >= 0 && cmds[i - 1].builtin))
			status = execute_builtin(pipes, cmds, i - 1, envp);
		else if (cmds[i].builtin && cmds[i + 1].builtin)
			status = execute_builtin(pipes, cmds, i, envp);
	}
	return (status);
}

int	executor(t_command *commands, char ***envp)
{
	pid_t	*pids;
	int		cmd_count;
	int		**pipes;
	int		status;
	int		fork_status;

	status = 0;
	cmd_count = ft_commands_len(commands);
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (1);
	pipes = ft_init_pipes(cmd_count, pids);
	if (!pipes)
		return (1);
	status = execute(pipes, pids, commands, envp);
	ft_close(pipes, cmd_count);
	ft_wait(cmd_count, pids, &fork_status);
	ft_free_all(pipes, pids, cmd_count);
	if (commands[cmd_count - 1].builtin)
		return (status);
	else
		return (fork_status);
}
