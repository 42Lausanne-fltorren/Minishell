/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:48:39 by fltorren          #+#    #+#             */
/*   Updated: 2024/03/18 15:49:06 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_close(int **pipes, int cmd_count)
{
	int	i;

	i = -1;
	while (++i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

void	ft_io_error(char *file)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	exit(1);
}

void	ft_setup_in(t_command cmd)
{
	int	fd[2];

	if (cmd.in)
	{
		fd[0] = open(cmd.in->value, O_RDONLY, 0644);
		if (fd[0] == -1)
			ft_io_error(cmd.in->value);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	else if (cmd.heredoc)
	{
		pipe(fd);
		ft_heredoc(cmd, fd);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
	}
}

void	ft_setup_out(t_command cmd)
{
	int	fd;

	if (cmd.out)
	{
		fd = open(cmd.out->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			ft_io_error(cmd.out->value);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (cmd.append)
	{
		fd = open(cmd.append->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			ft_io_error(cmd.append->value);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	ft_setup_io(int **pipes, int i, int cmd_count, t_command cmd)
{
	if (i == 0)
	{
		if (cmd_count > 1)
			dup2(pipes[i][1], STDOUT_FILENO);
		ft_setup_in(cmd);
	}
	else if (i < cmd_count - 1)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	else
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		ft_setup_out(cmd);
	}
	ft_close(pipes, cmd_count);
}
