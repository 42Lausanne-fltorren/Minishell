/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:26:36 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 23:27:17 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_token(t_token *token, char **envp, int lces)
{
	if (token->type == TOKEN_WORD)
	{
		if (token->value[0] == '$' && token->value[1] == '?')
		{
			free(token->value);
			token->value = ft_itoa(lces);
		}
		else
			token->value = replace_variables(token->value, envp);
	}
}

void	expand_tokens(t_token **tokens, char **envp, int lces)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		expand_token(tokens[i], envp, lces);
		i++;
	}
}

int	(*get_builtin(char *cmd))(t_token **args, char **envp, int fd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (ft_echo);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (ft_pwd);
	if (!ft_strncmp(cmd, "cd", 3))
		return (ft_cd);
	return (NULL);
}

void	expand_commands(t_command *commands, char **envp, int lces)
{
	int	i;

	i = 0;
	while (commands && commands[i].cmd)
	{
		expand_token(commands[i].cmd, envp, lces);
		if (commands[i].args)
			expand_tokens(commands[i].args, envp, lces);
		if (commands[i].in)
			expand_token(commands[i].in, envp, lces);
		if (commands[i].out)
			expand_token(commands[i].out, envp, lces);
		commands[i].builtin = get_builtin(commands[i].cmd->value);
		if (!commands[i].builtin)
			expand_cmd(commands[i].cmd, envp);
		i++;
	}
}
