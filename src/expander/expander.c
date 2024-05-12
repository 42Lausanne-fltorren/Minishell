/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fltorren <fltorren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 18:26:36 by fltorren          #+#    #+#             */
/*   Updated: 2024/04/19 23:57:04 by fltorren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_token(t_token *token, char **envp, int lces)
{
	char	*tmp;

	if (token->type == TOKEN_WORD)
	{
		if (ft_strnstr(token->value, "$?", ft_strlen(token->value)))
		{
			tmp = ft_itoa(lces);
			token->value = ft_replace_str(token->value, ft_strdup("$?"), tmp);
		}
		token->value = replace_variables(token->value, envp);
		clear_closed_brackets(token->value);
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

int	(*get_builtin(char *cmd))(t_token **args, char ***envp, int fd)
{
	if (!ft_strncmp(cmd, "echo", 5))
		return (ft_echo);
	if (!ft_strncmp(cmd, "pwd", 4))
		return (ft_pwd);
	if (!ft_strncmp(cmd, "cd", 3))
		return (ft_cd);
	if (!ft_strncmp(cmd, "env", 4))
		return (ft_env);
	if (!ft_strncmp(cmd, "exit", 5))
		return (ft_exit);
	if (!ft_strncmp(cmd, "export", 7))
		return (ft_export);
	if (!ft_strncmp(cmd, "unset", 6))
		return (ft_unset);
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
