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

static int	ft_error(char *val)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(val);
	return (1);
}

int	run_builtin(t_command cmd, char ***envp, int fd)
{
	if (cmd.open_error != NULL)
	{
		ft_putstr_fd(cmd.open_error, STDERR_FILENO);
		return (1);
	}
	if (cmd.out)
	{
		fd = open(cmd.out->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (ft_error(cmd.out->value));
	}
	else if (cmd.append)
	{
		fd = open(cmd.append->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (ft_error(cmd.append->value));
	}
	return (cmd.builtin(cmd.args, envp, fd));
}

char	**arr_dup(char **arr)
{
	int		i;
	char	**cpy;

	i = 0;
	while (arr[i])
		i++;
	cpy = malloc((sizeof(char *) * (i + 1)));
	i = -1;
	while (arr[++i])
		cpy[i] = ft_strdup(arr[i]);
	return (cpy);
}

int	ft_isdir(const char *fileName)
{
	struct stat	path;

	stat(fileName, &path);
	return (S_ISREG(path.st_mode));
}

char	*merge(t_token **args, int j)
{
	char	*dst;
	int		i;
	int		len;
	char	*tmp;

	i = j;
	while (args[i] && args[i]->space)
		len += ft_strlen(args[i++]->value);
	dst = malloc(sizeof(char) * (len + i - j));
	i = j;
	while (args[i] && args[i]->space)
	{
		tmp = dst;
		dst = ft_strjoin(tmp, args[i]->value);
		free(tmp);
		i++;
		if (args[i] && args[i]->space)
		{
			ft_strlcat(dst, " ", ft_strlen(dst) + 1);
		}
	}
	return (dst);
}