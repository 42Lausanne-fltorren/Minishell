/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 14:39:55 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/18 14:28:21 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != TOKEN_NULL)
	{
		free(tokens[i].value);
		tokens[i].value = NULL;
		i++;
	}
	free(tokens);
	tokens = NULL;
}

void	free_commands(t_command *commands)
{
	int	i;

	i = 0;
	while (commands && commands[i].cmd)
	{
		if (commands[i].args)
		{
			free(commands[i].args);
			commands[i].args = NULL;
		}
		if (commands[i].heredoc)
		{
			free(commands[i].heredoc);
			commands[i].heredoc = NULL;
		}
		i++;
	}
	free(commands);
}

void	ft_free_arr(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}
