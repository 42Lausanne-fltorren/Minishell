/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:49:19 by fltorren          #+#    #+#             */
/*   Updated: 2024/03/14 17:19:07 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_join_cmd(char *cmd, char *path)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	tmp2 = ft_strjoin(tmp, cmd);
	if (!tmp2)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (tmp2);
}

static char	*ft_get_cmd_path(char *cmd, char *path)
{
	char	**split;
	size_t	i;
	char	*tmp;

	if (!path)
		return (NULL);
	split = ft_split(path, ':');
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		tmp = ft_join_cmd(cmd, split[i]);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK) == 0)
		{
			ft_free_arr(split);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	ft_free_arr(split);
	return (NULL);
}

void	expand_cmd(t_token *token, char **envp)
{
	char	*cmd;

	if (token->value[0] == '.' || token->value[0] == '/')
		return ;
	cmd = ft_get_cmd_path(token->value, ft_getenv("$PATH", envp));
	free(token->value);
	if (!cmd)
		token->value = NULL;
	else
		token->value = cmd;
}
