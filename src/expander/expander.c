/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:26:36 by fltorren          #+#    #+#             */
/*   Updated: 2024/02/15 12:50:12 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_token(t_token *token, char **envp)
{
	if (token->type == TOKEN_WORD)
	{
		token->value = replace_variables(token->value, envp);
	}
}

void	expand_tokens(t_token **tokens, char **envp)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		expand_token(tokens[i], envp);
		i++;
	}
}

void	expand_commands(t_command *commands, char **envp)
{
	int	i;

	i = 0;
	while (commands && commands[i].cmd)
	{
		expand_token(commands[i].cmd, envp);
		if (commands[i].args)
			expand_tokens(commands[i].args, envp);
		if (commands[i].in)
			expand_token(commands[i].in, envp);
		if (commands[i].out)
			expand_token(commands[i].out, envp);
		expand_cmd(commands[i].cmd, envp);
		i++;
	}
}
